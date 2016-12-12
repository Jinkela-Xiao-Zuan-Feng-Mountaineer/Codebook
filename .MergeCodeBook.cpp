#include<Windows.h>
#include<iostream>
#include<cstdlib>
#include<fstream>
#include<iomanip>
#include<regex>
using namespace std;
ofstream fout;
ifstream fin;

static std::wstring CPToUTF16(unsigned code_page, const std::string& input)
{
    auto const size = MultiByteToWideChar(code_page, 0, input.data(), static_cast<int>(input.size()), nullptr, 0);

    std::wstring output;
    output.resize(size);

    if (size == 0 || size != MultiByteToWideChar(code_page, 0, input.data(), static_cast<int>(input.size()), &output[0], static_cast<int>(output.size())))
        output.clear();

    return output;
}

std::wstring UTF8ToUTF16W(const std::string &input)
{
    return CPToUTF16(CP_UTF8, input);
}
//CP_ACP
std::string UTF16ToUTF8(const std::wstring& input,unsigned codepage = CP_UTF8)
{
    auto const size = WideCharToMultiByte(codepage, 0, input.data(), static_cast<int>(input.size()), nullptr, 0, nullptr, nullptr);

    std::string output;
    output.resize(size);

    if (size == 0 || size != WideCharToMultiByte(codepage, 0, input.data(), static_cast<int>(input.size()), &output[0], static_cast<int>(output.size()), nullptr, nullptr))
        output.clear();

    return output;
}

stringstream ss;
string toLatex(string s,bool esc = true)
{
    replace(s.begin(),s.end(),'\\','/');
    if( s.find(' ')!=-1 ){
        cerr<<"名稱不允許\空白:"<<s<<endl;
    }
    if(esc){
        string tmp = s;
        s.clear();
        for(char c:tmp){
            if( c=='_'||c=='&' )s.push_back('\\');
            s.push_back(c);
        }
    }
    return s;
}
void merge(string root,int d=0)
{
    WIN32_FIND_DATAW fd;
    HANDLE hD = FindFirstFileW(UTF8ToUTF16W(root+"*").c_str(),&fd);
    string FileName;
    do{
        FileName = UTF16ToUTF8(fd.cFileName);
        if( FileName[0] == '.' )continue;
        if( fd.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY )
        {
            //cout<<"\\section{"<<FileName<<"}"<<endl;
            fout<<"\\section{"<<toLatex(FileName)<<"}"<<endl;
            merge(root+FileName+"\\",d+1);
            continue;
        }
        else if( FileName.back()=='p' )
        {
            //cout<<setw(d*2)<<""<<"\\includecpp{"<<FileName<<"}{"<<root+FileName<<"}"<<endl;
            fout<<setw(d*2)<<""<<"\\includecpp{"<<toLatex(FileName)<<"}{"<<toLatex(root+FileName,false)<<"}"<<endl;
        }else if( FileName=="formula.tex" || FileName=="java.tex" )
        {
            fout<<setw(d*2)<<""<<"\\includetex{"<<toLatex(FileName)<<"}{"<<toLatex(root+FileName,false)<<"}"<<endl;
        }
    }while(FindNextFileW(hD,&fd));
}
int main()
{
    fout.open("list.tex");
    merge(".\\");
    
    fout.close();
    cout<<endl;
    fout.open("README.md");
    fout<< ss.str();
    fout.close();
    system("PAUSE");
}
