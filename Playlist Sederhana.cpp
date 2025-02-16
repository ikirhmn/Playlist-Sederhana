#include <iostream>
#include <algorithm>
using namespace std;

int playlistSize = 0;

struct Song {
    string artist, genre, title;
    int year, duration_min, duration_sec;
};

Song playlist[100];

#include <iomanip> // Untuk mengatur lebar tampilan

void PrintPlaylist() {
    if (playlistSize == 0) {
        cout << "\nThere is no song added to your playlist!" << endl;
    } else {
        for (int i = 0; i < playlistSize; i++) {
            cout << setw(4) << i + 1 << "|" << playlist[i].artist << " - " << playlist[i].title << "(" << playlist[i].year << ")" << endl;
            cout << setw(6) << playlist[i].duration_min << ":" << setw(2) << setfill('0') << playlist[i].duration_sec;
            cout << setw(20) << setfill(' ') << "Genre : " << playlist[i].genre << endl;
        }
    }
}

int durasi(const string& duration) {
    int value = 0;
    size_t secPos = duration.find("sec");
    size_t minPos = duration.find("min");

    if (secPos != string::npos) {
        string sec = duration.substr(0, secPos);
        value = stoi(sec);
    } else if (minPos != string::npos) {
        string min = duration.substr(0, minPos);
        value = stoi(min);
    }

    return value;
}

bool CompareByTitle(const Song& a, const Song& b) {
    return a.title < b.title;
}

bool CompareByArtist(const Song& a, const Song& b) {
    return a.artist < b.artist;
}

bool CompareByYear(const Song& a, const Song& b) {
    return a.year < b.year;
}

bool CompareByDuration(const Song& a, const Song& b) {
    int durationA = a.duration_min * 60 + a.duration_sec;
    int durationB = b.duration_min * 60 + b.duration_sec;
    return durationA < durationB;
}

bool CompareByGenre(const Song& a, const Song& b) {
    return a.genre < b.genre;
}

template <bool (*CompareFunction)(const Song&, const Song&)>
bool CompareSongs(const Song& a, const Song& b) {
    return CompareFunction(a, b);
}

void DeleteSongByTitle(const string& title) {
    int index = -1;
    for (int i = 0; i < playlistSize; i++) {
        if (playlist[i].title == title) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < playlistSize - 1; i++) {
            playlist[i] = playlist[i + 1];
        }
        playlistSize--;
        cout << "Song with title '" << title << "' deleted successfully!" << endl;
    } else {
        cout << "Song with title '" << title << "' not found!" << endl;
    }
}

void DeleteSongByArtist(const string& artist) {
    int deletedCount = 0;
    for (int i = 0; i < playlistSize; i++) {
        if (playlist[i].artist == artist) {
            deletedCount++;
        } else {
            playlist[i - deletedCount] = playlist[i];
        }
    }
    playlistSize -= deletedCount;
    if (deletedCount > 0) {
        cout << "Deleted " << deletedCount << " song(s) by artist '" << artist << "' successfully!" << endl;
    } else {
        cout << "Song(s) by artist '" << artist << "' not found!" << endl;
    }
}


int main() {
    string input, command, artist, title, genre;
    int year, duration_min, duration_sec;
    while (true) {
        system("cls");
        cout << "------------------------------------------------" << endl;
        cout << "                  Your Playlist" << endl;
        cout << "------------------------------------------------" << endl;
        PrintPlaylist();

        cout << "------------------------------------------------" << endl;
        cout << "Command >>> ";
        getline(cin, input);

        size_t pos = input.find(' ');
        if (pos != string::npos) {
            command = input.substr(0, pos);
            input = input.substr(pos + 1);
        } else {
            command = input;
            input = "";
        }

        if (command == "add") {
            pos = input.find(',');
            artist = input.substr(0, pos);
            input = input.substr(pos + 2);

            pos = input.find(',');
            title = input.substr(0, pos);
            input = input.substr(pos + 2);

            pos = input.find(',');
            year = stoi(input.substr(0, pos));
            input = input.substr(pos + 2);

            pos = input.find(',');
            string duration = input.substr(0, pos);
            duration_min = durasi(duration);
            input = input.substr(pos + 2);

            pos = input.find(',');
            duration = input.substr(0, pos);
            duration_sec = durasi(duration);
            input = input.substr(pos + 2);

            genre = input;

            Song newSong;
            newSong.artist = artist;
            newSong.title = title;
            newSong.year = year;
            newSong.duration_min = duration_min;
            newSong.duration_sec = duration_sec;
            newSong.genre = genre;

            playlist[playlistSize] = newSong;
            playlistSize++;

            PrintPlaylist();
    
        } else if (command == "delete ") {
            if(command == title){
            pos = input.find(' ');
            title = input.substr(0, pos);
            input = input.substr(pos + 2);
            DeleteSongByTitle(title);
            }
            else if (command == artist){
            pos = input.find(' ');
            artist = input.substr(0, pos);
            input = input.substr(pos + 2);
            DeleteSongByArtist(artist);
            }
            
            PrintPlaylist();

        } else if (command == "quit") {
            break;
        } else {
            cout << "Invalid command!" << endl;
        }
    }

    return 0;
}
