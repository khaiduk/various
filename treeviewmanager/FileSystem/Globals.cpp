/**
///\file Globals.cpp
///\brief definicje metod klasy Globals
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////



#include "Globals.h"
#include <boost/filesystem.hpp>


using namespace boost::filesystem;

bool FileSystem::Globals::isEmpty(const Path& p)
{
    try{
        if(boost::filesystem::is_empty(p.getPath()))
            return true;
        else return false;
    }catch(...)
    {
      return true;
    }
}


FileSystem::Globals::type FileSystem::Globals::whatIs(const FileSystem::Path& p)
{
    try{
    if(boost::filesystem::is_regular_file(p.getPath()))
        return file;
    else if(boost::filesystem::is_directory(p.getPath()))
        return dir;
    else return other;
    }catch(...)
    {
        return other;
    }
}


void FileSystem::Globals::copy(const FileSystem::Path& skad, const FileSystem::Path& dokad, FileSystem::Globals::copy_move_option option)
{
  try{
    if(!boost::filesystem::is_directory(skad.getPath()))
    {
        if(option==FileSystem::Globals::fail_if_exists)
            boost::filesystem::copy_file(skad.getPath(), dokad.getPath(), boost::filesystem::copy_option::fail_if_exists);
        else boost::filesystem::copy_file(skad.getPath(), dokad.getPath(), boost::filesystem::copy_option::overwrite_if_exists);
    }else
    {
        boost::filesystem::copy_directory(skad.getPath(), dokad.getPath());

        boost::filesystem::directory_iterator iter(skad.getPath());
        string skadStr=(boost::filesystem::canonical((boost::filesystem::path(skad.getPath()))).string());
        string dokadStr=(boost::filesystem::canonical(dokad.getPath()).string());

        while(iter!=boost::filesystem::directory_iterator())
        {
            string iterStr=(boost::filesystem::canonical(((*iter).path())).string());

            iterStr.erase(0,skadStr.length()); //usuniêcie ca³ej œcie¿ki tak aby tylko pozosta³y nazwy
                                               //kolejnych plików/folderów w katalogu

            string dokadFinStr=dokadStr+'/'+iterStr; //finalna œcie¿ka do której chcemy skopiowaæ coœ

            FileSystem::Globals::copy((boost::filesystem::canonical(((*iter).path())).string()), dokadFinStr, option);

            ++iter;
        }

    }
  }catch(...)
  {

  }
}

bool FileSystem::Globals::createDir(const FileSystem::Path& sciezka)
{
    try{
       return boost::filesystem::create_directories(sciezka.getPath());
    }catch(...)
    {
    }

    return false;

}

bool FileSystem::Globals::exists(const FileSystem::Path& sciezka)
{
    boost::system::error_code err; //zamiast ³apaæ wyj¹tek ustawiamy kod b³êdu
    return boost::filesystem::exists(sciezka.getPath(), err);
}

void FileSystem::Globals::remove(const FileSystem::Path& sciezka)
{
    try
    {
        try{
            boost::filesystem::remove_all(sciezka.getPath());
        }catch(boost::filesystem::filesystem_error e) //jeœli jest b³¹d usówania to po kolei usówamy zawartoœæ
        {
                boost::filesystem::directory_iterator iter(sciezka.getPath());

                while(iter!=boost::filesystem::directory_iterator())
                {
                    try{
                        FileSystem::Globals::remove(boost::filesystem::canonical((*iter).path()).string());
                    }catch(boost::filesystem::filesystem_error e)
                    {

                    }

                    ++iter;
                }

       }

    }catch(...)
    {
    }
}

void FileSystem::Globals::rename(const FileSystem::Path& stara, const FileSystem::Path& nowa)
{
    try
    {
        boost::filesystem::rename(stara.getPath(), nowa.getPath());
    }catch(...)
    {

    }
}

void FileSystem::Globals::rename(const FileSystem::Path& stara, const char* nowaNazwa)
{
    string nowaStr=stara;
    string::iterator iter=nowaStr.end();
    string::iterator koniec=nowaStr.end();
    --koniec;
    for(;iter!=nowaStr.begin(); --iter) //w pêtli usówamy star¹ nazwê ze œcierzki
    {
        if((*iter=='\\' || *iter=='/') && iter!=koniec)
        {
            nowaStr.erase(iter, nowaStr.end());
            break;
        }
    }

    nowaStr+='/'+string(nowaNazwa); //teraz mo¿emy dokleiæ do œcie¿ki now¹ nazwê

    try
    {
        boost::filesystem::rename(stara.getPath(), nowaStr);
    }catch(...)
    {

    }
}


void FileSystem::Globals::move(const FileSystem::Path& skad, const FileSystem::Path& dokad, FileSystem::Globals::copy_move_option option)
{
    try{
        //jeœli miejsce docelowe jest na innym dysku:
        if(FileSystem::Globals::rootDirectory(skad)!=FileSystem::Globals::rootDirectory(dokad))
        {
            FileSystem::Globals::copy(skad, dokad, option);
            FileSystem::Globals::remove(skad);
        }else //jeœli na tym samym to zmiana œcie¿ki wystarczy
        {
            FileSystem::Globals::rename(skad,dokad);
        }
    }catch(...)
    {

    }
}

FileSystem::Path FileSystem::Globals::rootDirectory(const FileSystem::Path& p)
{
    string str=p;

    for(int i=(str.length()-1); i>=0; --i) //usówamy nazwê pliku/folderu ze œcie¿ki
    {
        if(str[i]=='/' || str[i]=='\\')
        {
            str.erase(i ,str.length());

        }else break;
    }

    for(unsigned int i=0; i<str.length(); ++i) //teraz jeœli œcie¿ka sk³ada siê z kilku zag³êbieñ to u¿ywamy funkcji boost::filesystem do dostania roota
    {
        if(str[i]=='/' || str[i]=='\\')
        {
            try{
                return (boost::filesystem::canonical((boost::filesystem::path(p.getPath()).root_path())).string());
            }catch(...)
            {

            }
        }
    }

    return p; //jeœli nie ma kilku zag³êbieñ to zwraca nam to co zosta³o
}


uintmax_t FileSystem::Globals::size(const Path& p)
{
    try{
        if(!boost::filesystem::is_directory(p.getPath()))
        {
            return boost::filesystem::file_size(p.getPath());
        }else
        {
            uintmax_t rozmiar=0;

            boost::filesystem::directory_iterator iter(p.getPath());
            while(iter!=boost::filesystem::directory_iterator())
            {
                rozmiar+=FileSystem::Globals::size((boost::filesystem::canonical(((*iter).path())).string()));
                ++iter;
            }
            return rozmiar;
        }

    }catch(...)
    {
      return 0;
    }
}


int FileSystem::Globals::positionTo(const Path& p1, const Path& p2)
{

    try{
        string strF=p1;
        string strS=p2;

        for(int i=(strF.length()-1); i>=0; --i)
        {
            if(strF[i]=='/' || strF[i]=='\\')
            {
                strF.erase(i ,strF.length());

            }else break;
        }

        for(int i=(strS.length()-1); i>=0; --i)
        {
            if(strS[i]=='/' || strS[i]=='\\')
            {
                strS.erase(i ,strS.length());

            }else break;
        }

        int s1=0;
        int s2=0;

        for(int i=(strF.length()-1); i>=0; --i)
        {
            if(strF[i]=='/' || strF[i]=='\\')
            {
                ++s1;

            }
        }

        for(int i=(strS.length()-1); i>=0; --i)
        {
            if(strS[i]=='/' || strS[i]=='\\')
            {
                ++s2;

            }
        }

        return s2-s1;

    }catch(...)
    {
      return 0;
    }
}


vector<FileSystem::Path> FileSystem::Globals::getDisks()
{
    vector<FileSystem::Path> vec=vector<FileSystem::Path>();
    const size_t buffer_size = 1024;
    TCHAR buffer[buffer_size];

    GetLogicalDriveStrings( buffer_size, buffer);
    TCHAR* tmp=buffer;

    while(*tmp)
    {
        wstring str(tmp);
        FileSystem::Path nowy=( FileSystem::Path(str));
        vec.push_back(nowy);
        tmp+=str.length()+1;
    }

    return vec;
}
