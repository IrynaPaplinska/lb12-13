#include <iostream>
#include <string>
#include <fstream>     // Для роботи з файлами (ifstream, ofstream)
#include <iomanip>     // Для форматування виводу
#include <algorithm>   // Для функції std::swap

using namespace std;

// --- Оголошення структури Train ---
struct Train {
    string destination;  // пункт призначення
    int number;          // номер потягу
    float time;          // час відправлення
};

const int N = 8;
const string INPUT_FILE = "trains_input.txt"; // Файл, з якого ЧИТАЄМО 
const string OUTPUT_FILE = "results.txt";     // Файл, куди ЗАПИСУЄМО вхідні дані

// -----------------------------------------------------------------
// ФУНКЦІЯ: Обробка даних потягів
// -----------------------------------------------------------------
void process_train_data() {
    
    Train trains[N];
    int records_read = 0;

    // --- ЕТАП 1: Зчитування даних з файлу trains_input.txt ---
    
    ifstream inputFile(INPUT_FILE);

    cout << "--- 1. Зчитування даних з файлу " << INPUT_FILE << " ---" << endl;

    if (!inputFile.is_open()) {
        cerr << "❌ ПОМИЛКА: Не вдалося відкрити вхідний файл " << INPUT_FILE << "!" << endl;
        return; // Завершення програми, якщо файл не знайдено
    }

    // Зчитування 8 записів (поля: destination, number, time)
    while (records_read < N && 
           inputFile >> trains[records_read].destination 
                   >> trains[records_read].number 
                   >> trains[records_read].time) 
    {
        records_read++;
    }

    inputFile.close(); 

    if (records_read != N) {
        cerr << "❌ ПОМИЛКА: Зчитано лише " << records_read << " записів замість " << N << " необхідних." << endl;
        return; 
    }
    
    cout << "✅ Усі 8 записів успішно зчитано з файлу." << endl;

    // --- ЕТАП 2: Запис зчитаних даних у файл results.txt ---
    
    ofstream outputFile(OUTPUT_FILE);

    if (outputFile.is_open()) {
        outputFile << "--- Введені дані про потяги (Зчитано з " << INPUT_FILE << ") ---" << endl;
        outputFile << "Destination\tNumber\tTime" << endl;
        
        for (int i = 0; i < N; i++) {
            // Записуємо дані у файл
            outputFile << trains[i].destination << "\t\t"
                       << trains[i].number << "\t\t"
                       << fixed << setprecision(2) << trains[i].time << endl;
        }
        outputFile.close();
        cout << "✅ Зчитані дані збережено у файл " << OUTPUT_FILE << "." << endl;
    } else {
         cerr << "❌ ПОМИЛКА: Не вдалося створити/відкрити вихідний файл " << OUTPUT_FILE << "." << endl;
    }
    
    // --- ЕТАП 3: Сортування за часом відправлення ---
    cout << "\n--- 2. Сортування масиву за часом ---" << endl;
    for (int i = 0; i < N - 1; i++) {
        for (int j = i + 1; j < N; j++) {
            if (trains[i].time > trains[j].time) {
                // Обмін цілими структурами
                swap(trains[i], trains[j]); 
            }
        }
    }
    cout << "✅ Масив потягів відсортовано за часом відправлення." << endl;

    // --- ЕТАП 4: Пошук потягів за пунктом призначення ---
    string city;
    cout << "\n--- 3. Пошук ---" << endl;
    cout << "Введіть назву міста для пошуку: ";
    cin >> city;

    bool found = false;
    cout << "\nПотяги, що прямують до " << city << " (відсортовані):" << endl;

    for (int i = 0; i < N; i++) {
        if (trains[i].destination == city) {
            cout << "Потяг №" << trains[i].number
                 << " | час: " << fixed << setprecision(2) << trains[i].time << endl;
            found = true;
        }
    }

    if (!found) {
        cout << "Потягiв до цього міста немає." << endl;
    }
}

int main() {
    process_train_data();
    return 0;
}