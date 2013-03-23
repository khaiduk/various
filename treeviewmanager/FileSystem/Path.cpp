/**
///\file Path.cpp
///\brief definicje metod klasy Path
///\author Chodorek Damian
///\date 14.06.2012
*/
///////////////////////////////////////////////////////////////////////////////////

#include "Path.h"
#include <boost/filesystem.hpp>


FileSystem::Path::operator wstring() const
{
    wstring wstr(path.length(), L' ');
    copy(path.begin(), path.end(), wstr.begin());

    return wstr;
}

FileSystem::Path::Path(const wstring& wstr)
{
    string str(wstr.length(), ' ');
    copy(wstr.begin(), wstr.end(), str.begin());

    for(int i=(str.length()-1); i>=0; --i) //usuniêcie zbêdnych slashow z koñca œcie¿ki
    {
        if(str[i]=='/' || str[i]=='\\')
        {
            str.erase(i ,str.length());

        }else break;
    }

    path=str;;
}

FileSystem::Path::Path(const string s)
{
    string str=s;
    for(int i=(str.length()-1); i>=0; --i)//usuniêcie zbêdnych slashow z koñca œcie¿ki
    {
        if(str[i]=='/' || str[i]=='\\')
        {
            str.erase(i ,str.length());

        }else break;
    }

    path=str;
}

FileSystem::Path::Path(const char* c)
{
    string str(c);
    for(int i=(str.length()-1); i>=0; --i)//usuniêcie zbêdnych slashow z koñca œcie¿ki
    {
        if(str[i]=='/' || str[i]=='\\')
        {
            str.erase(i ,str.length());

        }else break;
    }
    path=str;
}

FileSystem::Path::operator const char*() const
{
    return path.c_str();
}

FileSystem::Path::operator string() const
{
    return path;
}

string FileSystem::Path::getPath() const
{
    return path;
}

void FileSystem::Path::setPath(string str)
{
    for(int i=(str.length()-1); i>=0; --i)//usuniêcie zbêdnych slashow z koñca œcie¿ki
    {
        if(str[i]=='/' || str[i]=='\\')
        {
            str.erase(i ,str.length());

        }else break;
    }

    path=path;
}

bool FileSystem::Path::operator==(const FileSystem::Path& p) const
{
    try{
    if(boost::filesystem::exists(p.getPath()) && boost::filesystem::exists(path))
    {
        boost::system::error_code c;
        return boost::filesystem::equivalent(boost::filesystem::path(path),boost::filesystem::path(p.getPath()),c );
    }
    }catch(...)
    {

    } //jeœli boost::filesystem ma problem z porównaniem to robi to rêcznie

    string p1=p.getPath();
    string p2=path;

    for(unsigned int i=0; i<p1.length(); ++i)
    {
        if(p1[i]=='\\' || p1[i]=='/')
        {
            p1.erase(i,i+1);
        }
    }

    for(unsigned int i=0; i<p2.length(); ++i)
    {
        if(p2[i]=='\\' || p2[i]=='/')
        {
            p2.erase(i,i+1);
        }
    }

    if(p1[1]==':')
    {
        p1.erase(1,2);
    }
    if(p2[1]==':')
    {
        p2.erase(1,2);
    }

    if((p1[0]-p2[0]=='A'-'a') || (p2[0]-p1[0]=='A'-'a')) //sprawdzamy czy literki dysków ró¿ni¹ siê jedynie wielkoœci¹ litery
    {
        p1.erase(0,1);
        p2.erase(0,1);
    }

    return p1==p2;
}


bool FileSystem::Path::operator!=(const Path& p) const
{
    return !(*this==p);
}

