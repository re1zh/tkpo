#include <iostream>
#include <string>

using namespace std;

class AudioTrack {
    public:
        virtual ~AudioTrack() = default;
        virtual string getLanguage() const = 0;
        virtual string play() const = 0;
};

class Subtitles {
    public:
        virtual ~Subtitles() = default;
        virtual string getLanguage() const = 0;
        virtual string display() const = 0;
};

class RussianAudioTrack : public AudioTrack {
    public:
        string getLanguage() const override {
            return "Аудио: русский";
        }
        string play() const override {
            return "Язык аудио воспроизводится на русском.";
        }
};

class RussianSubtitleFile : public Subtitles {
    public:
        string getLanguage() const override {
            return "Субтитры: русские";
        }
        string display() const override {
            return "Субтитры отображаются на русском.";
        }
};

class EnglishAudioTrack : public AudioTrack {
    public:
        string getLanguage() const override {
            return "Audio: english";
        }
        string play() const override {
            return "Playing audio in English.";
        }
};

class EnglishSubtitleFile : public Subtitles {
    public:
        string getLanguage() const override {
            return "Subtitles: english";
        }
        string display() const override {
            return "Displaying subtitles in English.";
        }
};

class MovieFactory {
    public:
        virtual ~MovieFactory() = default;
        virtual AudioTrack* createAudioTrack() const = 0;
        virtual Subtitles* createSubtitles() const = 0;
};

class EnglishMovieFactory : public MovieFactory {
    public:
        AudioTrack* createAudioTrack() const override {
            return new EnglishAudioTrack();
        }
        Subtitles* createSubtitles() const override {
            return new EnglishSubtitleFile();
        }
};

class RussianMovieFactory : public MovieFactory {
public:
    AudioTrack* createAudioTrack() const override {
        return new RussianAudioTrack();
    }
    Subtitles* createSubtitles() const override {
        return new RussianSubtitleFile();
    }
};

class MovieRentalSystem {
    public:
        MovieRentalSystem(MovieFactory* initialFactory)
            : factory(initialFactory), audioTrack(nullptr), subtitleFile(nullptr) {
                updateContent();
            }

        ~MovieRentalSystem() {
            delete audioTrack;
            delete subtitleFile;
        }

        void setFactory(MovieFactory* newFactory) {
            delete audioTrack;
            delete subtitleFile;

            factory = newFactory;
            updateContent();
        }

        void playMovie() const {
            cout << audioTrack->play() << endl;
            cout << subtitleFile->display() << endl;
        }
    private:
        MovieFactory* factory;
        AudioTrack* audioTrack;
        Subtitles* subtitleFile;

        void updateContent() {
            audioTrack = factory->createAudioTrack();
            subtitleFile = factory->createSubtitles();
        }
};

int main() {
    EnglishMovieFactory englishFactory;
    MovieRentalSystem system(&englishFactory);

    cout << "Playing movie with initial settings:" << endl;
    system.playMovie();
    
    RussianMovieFactory russianFactory;
    system.setFactory(&russianFactory);

    cout << endl << "Playing movie after changing language:" << endl;
    system.playMovie();

    return 0;
}
