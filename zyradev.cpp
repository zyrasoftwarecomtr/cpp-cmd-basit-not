#include <iostream>
#include <fstream>
#include <string>
#include <vector>

struct Note {
    std::string title;
    std::string content;
};

void saveNotes(const std::vector<Note>& notes, const std::string& filename) {
    std::ofstream file(filename);
    if (!file) {
        std::cerr << "Notlar kaydedilemedi: " << filename << std::endl;
        return;
    }

    for (const Note& note : notes) {
        file << "Başlık: " << note.title << std::endl;
        file << "İçerik: " << note.content << std::endl;
        file << std::endl;
    }

    std::cout << "Notlar başarıyla kaydedildi." << std::endl;
}

void loadNotes(std::vector<Note>& notes, const std::string& filename) {
    std::ifstream file(filename);
    if (!file) {
        std::cerr << "Notlar yüklenemedi: " << filename << std::endl;
        return;
    }

    notes.clear();

    std::string line;
    while (std::getline(file, line)) {
        if (line.substr(0, 7) == "Başlık: ") {
            Note note;
            note.title = line.substr(7);
            std::getline(file, line); // İçerik satırını oku
            note.content = line.substr(9);
            notes.push_back(note);
        }
    }

    std::cout << "Notlar başarıyla yüklendi." << std::endl;
}

void showNotes(const std::vector<Note>& notes) {
    std::cout << "=== Notlar ===" << std::endl;

    for (const Note& note : notes) {
        std::cout << "Başlık: " << note.title << std::endl;
        std::cout << "İçerik: " << note.content << std::endl;
        std::cout << std::endl;
    }
}

int main() {
    std::vector<Note> notes;
    std::string filename = "notes.txt";

    loadNotes(notes, filename);

    while (true) {
        std::cout << "1. Notları Görüntüle" << std::endl;
        std::cout << "2. Not Ekle" << std::endl;
        std::cout << "3. Notları Kaydet" << std::endl;
        std::cout << "4. Çıkış" << std::endl;
        std::cout << "Seçiminizi yapın: ";

        int choice;
        std::cin >> choice;
        std::cin.ignore(); // Boşluğu temizle

        switch (choice) {
        case 1:
            showNotes(notes);
            break;
        case 2: {
            Note note;
            std::cout << "Başlık: ";
            std::getline(std::cin, note.title);
            std::cout << "İçerik: ";
            std::getline(std::cin, note.content);
            notes.push_back(note);
            std::cout << "Not başarıyla eklendi." << std::endl;
            break;
        }
        case 3:
            saveNotes(notes, filename);
            break;
        case 4:
            saveNotes(notes, filename);
            std::cout << "Uygulamadan çıkılıyor." << std::endl;
            return 0;
        default:
            std::cout << "Geçersiz seçim. Lütfen tekrar deneyin." << std::endl;
            break;
        }
    }

    return 0;
}
