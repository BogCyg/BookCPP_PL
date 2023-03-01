// ==========================================================================
//
// Oprogramowanie napisane przez prof. Bogusława Cyganka do użytku z książką:
// ==> Programowanie w języku C++. Wprowadzenie dla inżynierów. PWN 2023 <==
//
// Oprogramowanie jest dostarczane w stanie takim, w jakim jest, i do celów edukacyjnych
// bez żadnych gwarancji ani odpowiedzialności za jego użycie w jakiejkolwiek aplikacji.
//
// ==========================================================================
//
// Software written by Boguslaw Cyganek (C) to be used with the book:
// INTRODUCTION TO PROGRAMMING WITH C++ FOR ENGINEERS
// Published by Wiley, 2020
//
// The software is supplied as is and for educational purposes
// without any guarantees nor responsibility of its use in any application. 
//
// ==========================================================================




#include "HTTP_File.h"






#if _WIN32

	#include <urlmon.h>
	#pragma comment(lib, "urlmon.lib")

#elif __linux__

  #include <string>
  #include <filesystem> 
  #include <fstream>
  #include <curl/curl.h>

#elif macintosh

  // do zrobienia 

#endif


namespace CppBook
{


bool	HTTP_File_Body_Windows::Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName )
{
#if _WIN32   // Should be 1 on 32 bit and 64 bit Windows
	return URLDownloadToFile ( NULL, internet_addr.c_str(), localName.c_str(), 0, NULL ) == S_OK;
#else
	return false;
#endif
}




}	// CppBook


///////////////////////////////////////

// This can go to a differetn .cpp file
namespace CppBook
{



bool HTTP_File_Body_Linux::Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName )
{
#if __linux__   // Should be 1 on 32 bit and 64 bit Linux

  // Przykład użycia biblioteki CURL:
  // https://curl.se/libcurl/c/url2file.html

  // Jako funkcję callback użyjemy funkcję typu lambda - ale musi mieć pustą część przejmującą, czyli [].
  // W takim przypadku można ją będzie przekazać jak "zwykły" wskaźnik do funkcji w stylu C, czego wymaga biblio CURL.
  auto callback_lambda =  []( void * ptr, size_t size, size_t nmemb, void * theFile ) -> auto
                          {
                            std::ofstream * outFile = reinterpret_cast< std::ofstream * >( theFile );
                            const auto bytes_2_write = size * nmemb;      
                            outFile->write( reinterpret_cast< char * >( ptr ), bytes_2_write );
                            return bytes_2_write;
                          };

  
  std::ofstream outFile( std::filesystem::path( localName ), std::ios::binary );  // jako bufora używamy "zwykły" plik (a nie wide char)
  if( ! outFile.is_open() ) 
    return false;           // błąd podczas otwierania pliku do zapisu (niepoprawna ścieżka?)


  CURL * curl = curl_easy_init();  
  if( ! curl ) 
    return false;           // błąd w inicjalizacji CURL

  std::string tmp_url( internet_addr.begin(), internet_addr.end() );  // konwersja adresu z wstring do string (wymagane przez CURL)
  curl_easy_setopt( curl, CURLOPT_URL, tmp_url.c_str() );
  curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, + callback_lambda ); // + to trik aby skonwertować lambda do zwykłego wskaźnika do funkcji
  curl_easy_setopt( curl, CURLOPT_WRITEDATA, & outFile );
  auto res = curl_easy_perform( curl) ;
  curl_easy_cleanup( curl );

  return res == CURLE_OK;

#else
  return false;
#endif
}



}	// CppBook


///////////////////////////////////////

// This can go to a differetn .cpp file
namespace CppBook
{


bool	HTTP_File_Body_MacOS::Load_HTTP_File( const std::wstring & internet_addr, const std::wstring & localName )
{
#if macintosh   // Should be 1 on Apple
	return false;		// To be implemented
#else
	return false;
#endif
}




}	// CppBook




