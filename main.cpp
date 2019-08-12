//
//  main.cpp
//  EditUrls
//
//  Created by Marisa Johnson on 7/29/19.
//  Copyright © 2019 Marisa Johnson. All rights reserved.
//

#include <iostream>
#include <string>
#include <queue>
#include <fstream>

// queue of API URLs
std::queue<std::string> apiURLs;
// queue of clean Ada Louise Huxtable article URLs
std::queue<std::string> cleanURLs;

// Function purpose: generate URL for pages 1-100
// Function parameter: none
// Function return: queue
std::queue<std::string> pageGen()
{
    std::string tempUrl = "";
    
    // loop through however many pages are available
    for (int i = 0; i < 150; i++)
    {
        // generate URL with proper page number
        // limit search to articles with "Ada Louise Huxtable"
        // limit search to articles published before Jan 7, 2013
        // limit results to URLs
        tempUrl = "https://api.nytimes.com/svc/search/v2/articlesearch.json?q=persons:(\"Ada Louise Huxtable\")&fl=web_url&page=" + std::to_string(i) + "&api-key=wCUyIvp0Jw5gBxU90D1VQjYG06T1LuCM";
        
        // add generated URL to queue
        apiURLs.push(tempUrl);
    }
    
    return apiURLs;
}

// Function purpose: extract URLs from web page
// Function parameter: web page text
// Function return: none
void cleanText (const std::string& fileName)
{
    // open file of web page text
    std::ifstream data(fileName);
    
    // check that file is open
    if (!data.is_open())
    {
        std::cout << "Text file is not open!" << std::endl;
    }
    
    // begins with https
    std::string begin = "https";
    // ends with "}
    std::string end = "\"}";
    
    std::size_t foundBegin = -1;
    std::size_t foundEnd = -1;
    
    std::string dataLine;
    
    while (!data.eof())
    {
        // read in the lines
        // 10 URLs in each line
        std::getline(data, dataLine);
        
        for (int i = 0; i < 10; i++)
        {
            // URL is between https and .html
            // searches starting at the index after previous foundBegin index
            foundBegin = dataLine.find(begin, foundBegin + 1);
            //std::cout << "begin " << i  << " = " << foundBegin << ", " << dataLine[foundBegin] << dataLine [foundBegin + 1] << dataLine [foundBegin + 2] << dataLine [foundBegin + 3] << std::endl;
            // foundBegin variable now equals the index of where the https begins
            
            if (foundBegin == std::string::npos)
            {
                // no "https" present
                // continue out of loop
                continue;
            }
            
            // searches starting at the index after previous foundEnd index
            foundEnd = dataLine.find(end, foundEnd + 1);
            //std::cout << "end " << i  << " = " << foundEnd << ", " << dataLine[foundEnd] << dataLine[foundEnd + 1] << std::endl;
            // foundEnd variable now equals the index of where the html begins
            
            if (foundEnd == std::string::npos)
            {
                // no "} present
                // continue out of loop
                continue;
            }
            
            // create a substring of the URL
            std::string currURL = dataLine.substr(foundBegin, (foundEnd - foundBegin));
            
            // add currURL to queue of clean URLs
            cleanURLs.push(currURL);
        }
    }
}


int main(int argc, const char * argv[])
{
    int userChooses = 0;
    
    bool run = true;
    
    while (run)
    {
        std::cout << "What do you want to do?\n1. Generate list of New York Times Web Developer API URLs.\n2. Generate list of 10 New York Times articles held at an API URL.\n3. Quit\n\tI want to... ";
        std::cin >> userChooses;
        
        if (userChooses == 1)
        {
            // generate 150 web pages with 10 URLs each
            pageGen();
            while (!apiURLs.empty())
            {
                std::cout << apiURLs.front() << std::endl;
                /*for (int i = 0; i < 9; i++)
                 {
                 std::cout << std::endl;
                 }*/
                apiURLs.pop();
            }
            std::cout << std::endl;
        }
        
        else if (userChooses == 2)
        {
            // extract URL from each web page's contents
            //std::string dirtyFile = "";
            //std::cout << "Text file with API web pages: ";
            //std::getline(std::cin, dirtyFile);
            
            // cleans URLs from dirty web page
            //cleanText(dirtyFile);
            cleanText("ALHWebPages.txt");
            
            while (!cleanURLs.empty())
            {
                std::cout << cleanURLs.front() << std::endl;
                cleanURLs.pop();
            }
            std::cout << std::endl;
        }
        
        else if (userChooses == 3)
        {
            return 0;
        }
        else
        {
            std::cout << "Invalid input!" << std::endl;
            std::cout << std::endl;
            continue;
        }
    }
    
    return 0;
}
