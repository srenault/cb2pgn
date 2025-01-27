#include "cb2pgn_cgo.h"
#include "db_database.h"
#include "db_pgn_reader.h"
#include "db_log.h"
#include "db_pgn_writer.h"
#include "u_zstream.h"
#include "u_progress.h"
#include "m_ifstream.h"

#include <cstring>

static ProgressCallback g_progressCallback = nullptr;

static unsigned const g_Flags = db::Writer::Flag_Include_Variations
    | db::Writer::Flag_Include_Comments
    | db::Writer::Flag_Include_Annotation
    | db::Writer::Flag_Include_Marks
    | db::Writer::Flag_Include_Termination_Tag
    | db::Writer::Flag_Include_Mode_Tag
    | db::Writer::Flag_Include_Setup_Tag
    | db::Writer::Flag_Include_Variant_Tag
    | db::Writer::Flag_Include_Time_Mode_Tag
    | db::Writer::Flag_Exclude_Extra_Tags
    | db::Writer::Flag_Symbolic_Annotation_Style;

struct Progress : public util::Progress {
    void update(unsigned progress) override {
        if (g_progressCallback) {
            g_progressCallback(progress);
        }
    }

    void finish() throw() override {}
};

struct Log : public db::Log {
    bool error(db::save::State code, unsigned gameNumber) {
        const char* msg = nullptr;
        switch (code) {
            case db::save::Ok: return true;
            case db::save::UnsupportedVariant: return true;
            case db::save::DecodingFailed: return true;
            case db::save::GameTooLong: msg = "Game too long"; break;
            case db::save::FileSizeExeeded: msg = "File size exceeded"; break;
            case db::save::TooManyGames: msg = "Too many games"; break;
            case db::save::TooManyPlayerNames: msg = "Too many player names"; break;
            case db::save::TooManyEventNames: msg = "Too many event names"; break;
            case db::save::TooManySiteNames: msg = "Too many site names"; break;
            case db::save::TooManyRoundNames: msg = "Too many round names"; break;
            case db::save::TooManyAnnotatorNames: return true;
        }
        return code == db::save::GameTooLong;
    }

    void warning(Warning code, unsigned gameNumber) {}
};

void SetProgressCallback(ProgressCallback callback) {
    g_progressCallback = callback;
}

int ConvertToPgn(const char* cbhFilePath, const char* outputDir) {
    if (!cbhFilePath || !outputDir) {
        return -1;
    }

    try {
        db::tag::initialize();
        db::castling::initialize();
        db::Board::initialize();
        db::HomePawns::initialize();
        db::Signature::initialize();

        mstl::string convertto("utf-8");
        mstl::string convertfrom("auto");

        // Ensure .cbh extension
        mstl::string cbhPath(cbhFilePath);
        if (cbhPath.size() < 4 || strcmp(cbhPath.c_str() + cbhPath.size() - 4, ".cbh") != 0) {
            cbhPath += ".cbh";
        }

        // Create output PGN path
        mstl::string pgnPath = cbhPath;
        mstl::string::size_type n = pgnPath.find_last_of('/');
        if (n != mstl::string::npos) {
            pgnPath = pgnPath.substr(n + 1);
        }
        if (pgnPath.size() >= 4 && strcmp(pgnPath.c_str() + pgnPath.size() - 4, ".cbh") == 0) {
            pgnPath = pgnPath.substr(0, pgnPath.size() - 4);
        }
        if (pgnPath.size() < 4 || strcmp(pgnPath.c_str() + pgnPath.size() - 4, ".pgn") != 0) {
            pgnPath += ".pgn";
        }

        mstl::string fullPgnPath(outputDir);
        fullPgnPath += "/";
        fullPgnPath += pgnPath;

        Progress progress;
        db::Database src(cbhPath, convertfrom, db::Database::ReadOnly, progress);

        util::ZStream strm(fullPgnPath.c_str(), util::ZStream::Text, mstl::ios_base::out | mstl::ios_base::app);
        db::PgnWriter writer(db::format::Pgn, strm, convertto, g_Flags);

        unsigned numGames = src.countGames();
        Log log;
        unsigned countGames = 0;

        util::ProgressWatcher watcher(progress, numGames);
        progress.setFrequency(mstl::min(5000u, mstl::max(numGames/100, 1u)));

        for (unsigned i = 0; i < numGames; ++i) {
            db::save::State state = src.exportGame(i, writer);
            if (state == db::save::Ok) {
                ++countGames;
            } else if (!log.error(state, i)) {
                return countGames;
            }
        }

        return countGames;
    } catch (const std::exception&) {
        return -1;
    }
} 