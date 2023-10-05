#pragma once

#include <sstream>
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

std::string GetFileName (bool save) {
    char filename[1024];
    FILE *f;
    if (save) 
        f = popen("zenity --file-selection --save --file-filter=*.txt", "r");
    else
        f = popen("zenity --file-selection --file-filter=*.txt", "r");
    fgets(filename, 1024, f);
    if (filename[0] != '/') {
        return "-1";
    }
    std::string FileName;
    if (save)
        std::cout << "Saved to File : ";
    else
        std::cout << "Opened File : ";
    for (int i = 0; i < 1024; i++) {
        if (filename[i] == '\0' || filename[i] == '\n')
            break;
        std::cout << filename[i];
        FileName += filename[i];
    }
    std::cout << std::endl;
    return FileName;
}

void OpenFile () {
    std::string FileName = GetFileName (false);
    if (FileName[0] != '/')
        return;
    std::ifstream stream(FileName);
    std::string line;
    
}

void SaveFile () {
    std::string FileName = GetFileName (true);
    if (FileName[0] != '/')
        return;
    std::ofstream stream(FileName);

    stream.close();
}