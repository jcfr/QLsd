
// Qt includes
#include <QDebug>
#include <QLibrary>
#include <QFileInfo>

// QtLdd includes
#include "ctkCommandLineParser.h"

// STD includes
#include <cstdlib>
#include <iostream>

namespace 
{
void printUsage(const ctkCommandLineParser& parser)
{
  std::cout << "Usage\n" << std::endl;
  std::cout << "  qlsd [options] <path-to-library> <symbol-name>" << std::endl;
  std::cout << "\n\nOptions" << std::endl;
  std::cout << qPrintable(parser.helpText()) << std::endl;
}
}

int main(int argc, char** argv)
{
  ctkCommandLineParser parser;
  parser.setArgumentPrefix("--", "-");
  parser.addArgument("help", "h", QVariant::Bool, "Display available command line arguments.");
  
  // Parse the command line arguments
  bool ok = false;
  QHash<QString, QVariant> parsedArgs = parser.parseArguments(argc, argv, &ok);
  if (!ok)
    {
    std::cerr << "Error parsing arguments:" << qPrintable(parser.errorString()) << std::endl;
    return EXIT_FAILURE;
    }
    
  // Show a help message
  if (parsedArgs.contains("help"))
    {
    printUsage(parser);
    return EXIT_SUCCESS;
    }
    
  // Expects the following arguments: </path/to/lib> <symbol_name>
  if (parser.unparsedArguments().count() != 2)
    {
    printUsage(parser);
    return EXIT_SUCCESS;
    }
  
  QString libraryPath = parser.unparsedArguments().at(0);
  QString symbol = parser.unparsedArguments().at(1);
  
  std::cout << "Analysing [" << qPrintable(libraryPath) << "] ..." << std::endl;
  
  // Is <path-to-library> an absolute path ?
  if (!QFileInfo(libraryPath).isAbsolute())
    {
    std::cerr << "<path-to-library> should be an absolute path !\n" << std::endl;
    printUsage(parser);
    return EXIT_FAILURE;
    }
  
  // Does <path-to-library> point to a valid filename ?
  if (!QLibrary::isLibrary(libraryPath))
    {
    std::cerr << "<path-to-library> should be an absolute path !\n" << std::endl;
    printUsage(parser);
    return EXIT_FAILURE;
    }
  
  QLibrary library(libraryPath);
  
  bool loaded = library.load();
  if (!loaded)
    {
    std::cerr << "Failed to load the given library !\n" 
              << qPrintable(library.errorString()) << std::endl;
    return EXIT_FAILURE;
    }
  
  void * resolvedSymbol = library.resolve(symbol.toLatin1());
  if (!resolvedSymbol)
    {
    std::cerr << qPrintable(library.errorString())  << std::endl;
    return EXIT_FAILURE;
    }
  
  std::cout << "Successfully resolved symbol [" << qPrintable(symbol) << "] => " << resolvedSymbol << std::endl;
  return EXIT_SUCCESS;
}


