#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <limits>
using namespace std;

void waitForEnter()
{
    cout << "\n\nPress Enter to continue...";
    cin.clear();
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cin.get();
    system("cls");
}

void hangman(int number)
{
    if (number == 7)
    {
        cout << "                    \n";
        cout << "               \\O  \n";
        cout << "                |\\ \n";
        cout << "               / \\ \n";
    }
    else if (number == 6)
    {
        cout << "                     \n";
        cout << "                O    \n";
        cout << "               /|\\  \n";
        cout << "               / \\  \n";
    }
    else if (number == 5)
    {
        cout << "   _\n";
        cout << "  |_               O   \n";
        cout << " -|_              /|\\ \n";
        cout << "  |_              / \\ \n";
    }
    else if (number == 4)
    {
        cout << "   ___                 \n";
        cout << "  |___             O   \n";
        cout << " -|___            /|\\ \n";
        cout << "  |___            / \\ \n";
    }
    else if (number == 3)
    {
        cout << "   ___                  \n";
        cout << "  |___|             O   \n";
        cout << " -|___|            /|\\ \n";
        cout << "  |___|            / \\ \n";
    }
    else if (number == 2)
    {
        cout << "   ___                   \n";
        cout << "  |___|*******       O   \n";
        cout << " -|___|*******      /|\\ \n";
        cout << "  |___|*******      / \\ \n";
    }
    else if (number == 1)
    {
        cout << "   ___                   \n";
        cout << "  |___|************  O   \n";
        cout << " -|___|************ /|\\ \n";
        cout << "  |___|************ / \\ \n";
    }
    else if (number <= 0)
    {
        cout << " ______________ \n";
        cout << " |             |\n";
        cout << " |   X     X   |\n";
        cout << " |             |\n";
        cout << " |     OOO     |\n";
        cout << " |_____________|\n";
    }
    else if (number == 10)
    {
        cout << " ______________\n";
        cout << " |             |\n";
        cout << " |   O     O   |\n";
        cout << " |             |\n";
        cout << " |   \\_____/   |\n";
        cout << " |_____________|\n";
    }
}

int validation(int minRange, int maxRange) {
    int input;
    while (true) {
        cout << "Enter your desirable difficulty (1-3): ";
        cin >> input;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter a number.\n";
        } else if (input < minRange || input > maxRange) {
            cout << "Invalid range. Please enter a number between " << minRange << " and " << maxRange << ".\n";
        } else {
            break;
        }
    }
    return input;
}

int main()
{
    int difficulty, steps = 8, win = 0, size = 5, count_used_words=0;
    string word, word2;
    string used_words[26];
    for (int i = 0; i < 10; i++) {
        used_words[i] = '*';
    }
    string easy[size] = {"book", "moon", "tree", "song", "fish"};
    string normal[size] = {"orange", "planet", "garden", "purple", "monkey"};
    string hard[size] = {"default", "country", "rainbow", "desktop", "forever"};
    cout << "Welcome to the Hangman's Game!" << endl;
    difficulty = validation(1, 3);
    srand(static_cast<unsigned int>(time(0))); // setting timer for random
    if (difficulty == 1)
    {
        int random_word = rand() % (size); // getting a random number
        word = easy[random_word-1];
    }
    else if (difficulty == 2)
    {
        int random_word = rand() % (size);
        word = normal[random_word-1];
    }
    else if (difficulty == 3)
    {
        int random_word = rand() % (size);
        word = hard[random_word-1];
    }
    for (int i = 0; i < word.length(); i++)
    {
        word2 += "*";
    }
    cout << "\nLet's begin! You've chosen level " << difficulty << " of difficulty!\n";
    while (win == 0)
    {
        string letter;
        bool not_alpha = false;
        cout << "Your hidden word: ";
        for (int i = 0; i < word2.length(); i++)
        {
            cout << word2[i];
        }
        cout << "\nUsed letters: ";
        for (int i = 0; i < 10; i++) {
            if (used_words[i] != "*") {
                cout << used_words[i] << ' ';
            }
        }
        cout << "\nYour amount of attempts: " << steps << "\nGive us your letter! (write 'uno' to write a word): ";
        cin >> letter;
        for (int i = 0; i < letter.length(); i++)
        {
            letter[i] = tolower(letter[i]);
            if (!isalpha(letter[i]))
            {
                not_alpha = true;
            }
        }

        if (not_alpha or (letter.length() > 1 and letter != "uno"))
        {
            while (not_alpha or (letter.length() > 1 and letter != "uno"))
            {
                cout << "Your input is incorrect! Write another: ";
                cin >> letter;
            }
        }
        if (letter == "uno")
        {
            string full_word;
            cout << "Well, what is your word then: ";
            cin >> full_word;
            if (full_word == word)
            {
                cout << "\nWow, that's right!\n\n";
                win = 1;
            }
            else
            {
                cout << "\nWrong!!!\n\n";
                steps -= 3;
                hangman(steps);

                if (steps > 0)
                {
                    waitForEnter();
                }
            }
        }
        else
        {
            int fin = word.find(letter);

            if (fin != -1)
            {
                cout << "Right! Open the letter: " << letter << "\n\n";
                for (int i = 0; i < word.length(); i++)
                {
                    if (letter[0] == word[i])
                    {
                        word2[i] = letter[0];
                    }
                }
                cout << "Word: " << word2 << endl;
            }
            else if (fin == -1)
            {
                cout << "Wrong!!!\n";
                steps--;
                used_words[count_used_words] = letter;
                count_used_words++;
                hangman(steps);
                waitForEnter();
            }
        }

        int word_is_open = word2.find('*');

        if (steps <= 0)
        {
            cout << "Game Over! Your attempts are gone!\n";
            win = 2;
        }

        if (word_is_open == -1)
        {
            cout << "You won!";
            win = 1;
        }
    }
    if (win == 2)
    {
        cout << "\nYour word has been: " << word << "\n\n";
        hangman(0);
    }
    else if (win == 1)
    {
        cout << "\nYour word has been: " << word << "\n\n";
        hangman(10);
        cout << steps << " attempts left!";
    }
}
