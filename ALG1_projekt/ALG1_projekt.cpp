#include <iostream>
#include <vector>
#include <fstream>
#include <string>

int max_hodnota_vstupu(const std::string& filename) {
    std::ifstream vstupni_soubor(filename); //open the file

    if (!vstupni_soubor) { //check if the file is opened successfully
        std::cout << "Error opening file!" << std::endl;
        return -1;
    }

    std::string radek;
    std::string cislo1;
    std::string cislo2;
    int max = 0;
    int pomocny;
    while (getline(vstupni_soubor, radek)) { //read each line of the file
        std::size_t space_pos = radek.find(' '); //find the position of the first space
        std::string cislo1 = radek.substr(0, space_pos); //get the substring before the space
        pomocny = std::stoi(cislo1);
        if (pomocny > max) {
            max = pomocny;
        }
        std::string cislo2 = radek.substr(space_pos + 1);
        pomocny = std::stoi(cislo2);
        if (pomocny > max) {
            max = pomocny;
        }
    }
    vstupni_soubor.close(); //close the file

    return max+1;
}

int projit_graf(bool*** pole, bool** projdute_vrcholy, std::vector<int>* todo, int* max_value, int aktual_pocet=1) {//vsude pointry :-) krome velikosti
    std::cout << "testf" << std::endl;
    if (todo->size() == 0)return aktual_pocet;
    int aktualni_index= todo->back();//init jako posl prvek v todo
    todo->pop_back();
    //while (true) {
        //if (todo size == 0)return aktual_pocet;

        for (int i = aktualni_index; i < *max_value; ++i) {
            std::cout << "testf" << std::endl;
            if (*projdute_vrcholy[i]) {
                continue;
            }
            std::cout << "testfx" << std::endl;
            *projdute_vrcholy[i] = true;
            //odstranit projduty vrchol z todo (posl prvek)
            todo->pop_back();
            aktual_pocet++;
            for (int j = i + 1; j < *max_value; ++j) {
                std::cout << "testff" << std::endl;
                bool element = *pole[i][j];
                std::cout << "testff" << std::endl;
                if (element && !(*projdute_vrcholy[j])) {
                    std::cout << "testff" << std::endl;
                    //pridat j do vektoru ktery mam projit
                    todo->push_back(j);
                    std::cout << "testff" << std::endl;
                }
                std::cout << "testff" << std::endl;

            }
            std::cout << "testf" << std::endl;
        }
        return projit_graf(pole, projdute_vrcholy, todo, max_value, aktual_pocet);
    //}
}

int main()
{
    std::ifstream input_file("graph1.txt");

    // Check if the last line is empty (i.e., there is no newline character at the end)
    std::string last_line;
    if (input_file.seekg(-1, std::ios_base::end) && input_file.get() == '\n') {
        std::cout << "File already has a newline character at the end." << std::endl;
    }
    else {
        std::cout << "File does not have a newline character at the end." << std::endl;
        input_file.clear(); // clear the EOF flag
        input_file.close();

        // Open the file in append mode and write a newline character
        std::ofstream output_file("graph1.txt", std::ios_base::app);
        output_file << "\n";
        output_file.close();
    }


    int max_value = max_hodnota_vstupu("graph1.txt");
    std::cout << "Max value: " << max_value << std::endl;
    bool** pole = new bool* [max_value];
    for (int i = 0; i < max_value; ++i) {
        pole[i] = new bool[max_value];
        memset(pole[i], false, max_value * sizeof(bool));
    }
    std::cout << "allokace ok" << std::endl;
    
    std::ifstream vstupni_soubor("graph1.txt"); //open the file
    if (!vstupni_soubor) { //check if the file is opened successfully
        std::cout << "Error opening file!" << std::endl;
        return 1;
    }
    std::string radek;
    std::string cislo1;
    std::string cislo2;
    int prvni;
    int druhy;
    while (getline(vstupni_soubor, radek)) { //read each line of the file
        std::size_t space_pos = radek.find(' '); //find the position of the first space
        if (space_pos == std::string::npos) {
            // handle error: there is no space character in the string
            break;
        }
        std::string cislo1 = radek.substr(0, space_pos); //get the substring before the space
        prvni = std::stoi(cislo1);
        std::string cislo2 = radek.substr(space_pos + 1, radek.length() - space_pos - 1);
        druhy = std::stoi(cislo2);
        //std::cout << prvni << "_" << druhy << std::endl;
        pole[prvni][druhy] = true;
        pole[druhy][prvni] = true;
        //std::cout << "test" << std::endl;
    }
    std::cout << "test2" << std::endl;
    vstupni_soubor.close(); //close the file
    
    int pocet_vrcholu_max_komponenty = 0;
    int zacatecni_index_max_komponenty;
    int aktualni_zac;
    int aktual_pocet=1;
    std::vector<int> todo;//vector int todo dal projit
    bool* projdute_vrcholy = new bool[max_value];
    std::fill_n(projdute_vrcholy, max_value, false);
    for (int i = 0; i < max_value; ++i) {
        if (projdute_vrcholy[i]) {
            continue;
        }
        aktualni_zac = i;
        projdute_vrcholy[i] = true;
        std::cout << "test" << std::endl;
        for (int j = i + 1; j < max_value; ++j) {
            bool element = pole[i][j]; 
            if (element && !projdute_vrcholy[j]) {
                //pridat j do todo
                todo.push_back(j);
            }
             
        }
        std::cout << "test" << std::endl;
        aktual_pocet = projit_graf(&pole, &projdute_vrcholy, &todo, &max_value, aktual_pocet);
        std::cout << "test" << std::endl;
            //porovnat maxy vrcholu a popr prepsat
        if (aktual_pocet > pocet_vrcholu_max_komponenty) {
            pocet_vrcholu_max_komponenty = aktual_pocet;
            zacatecni_index_max_komponenty = aktualni_zac;
        }
    }
    
    

    



    int pocet_hran_komponenty = 0;


    int min_stupen_vrcholu_komponenty;
    int max_stupen_vrcholu_komponenty;
    int prum_stupen_vrcholu_komponenty;





    delete[] projdute_vrcholy;
    for (int i = 0; i < max_value; ++i) {
        delete[] pole[i];
    }
    delete[] pole;

    return 0;

}
