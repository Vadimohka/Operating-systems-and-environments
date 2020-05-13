using System;
using System.Collections.Generic;
using System.IO;

namespace Lab01
{
    class Program
    {
        static List<string> FoundFiles(string[] result, string pathForSearch)
        {
            string printRes = "\nFound files on " + pathForSearch + " :\n";
            List<string> allFiles = new List<string>();
            foreach (string folder in result)
            {
                try
                {
                    string[] files = Directory.GetFiles(folder, "*test*" + "*.txt", SearchOption.AllDirectories);
                    foreach (string file in files)
                    {
                        printRes += file + "\n";
                        allFiles.Add(file);
                    }
                }
                catch
                {
                    continue;
                }
            }
            if (allFiles.Count != 0)
            {
                Console.WriteLine(printRes);
            }               
            else
            {
                Console.WriteLine("\nNothing found");
            }
            return allFiles;
        }

        static void WriteResult(string resultFile, List<string> allFiles)
        {
            List<string> resultText = new List<string>();
            foreach (string file in allFiles)
            {
                resultText.AddRange(File.ReadAllLines(file));
            }
            File.AppendAllLines(resultFile, resultText);
        }

        static void Search(string pathForSearch, string resultFile)
        {
            Console.WriteLine($"Searching files on {pathForSearch} drive...");
            string[] result = Directory.GetDirectories(pathForSearch);
            List<string> allFiles = FoundFiles(result, pathForSearch);
            WriteResult(resultFile, allFiles);
        }

        static void Main(string[] args)
        {
            Search("D:\\", "D:\\labs 6 sem\\OSiS\\Lab01\\Lab01\\result.txt");
        }
    }
}
