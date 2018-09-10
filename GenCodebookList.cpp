#include<bits/stdc++.h>

#ifdef _WIN32
#include<Windows.h>
#endif

using namespace std;
using ll = long long;

string exec(const char *cmd)
{
    const int size = 1024;
    char buf[1024];

    string result;
    shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    
    if( !pipe ) 
    {
        cerr<<"popen() fail!"<<endl;
    }
    
    while( !feof(pipe.get()) )
    {
        if( fgets(buf, size, pipe.get()) != nullptr )
            result += buf;
    }
    return result;
}

string file_prefix()
{
    #ifdef _WIN32
    return ".\\";
    #else
    return "./";
    #endif
}

char spliter()
{
    #ifdef _WIN32
    return '\\';
    #else
    return '/';
    #endif
}

map<string,string> requireFile {
    {".cpp","includecpp"},
    {".tex","includetex"}
};

bool isTexFile(string name)
{
    if( name.size()<=4 ) return false;
    return name.substr(name.size()-4)==".tex";
}

bool isIgnored(string name)
{
    if(name.substr(0,4) == ".git") return true;
    if(name.find(spliter()) == string::npos) return true;
    if(name.size() <= size_t(4)) return true;
    string tmp = name.substr(name.size() - size_t(4));
    return requireFile.find(tmp) == requireFile.end();
}
vector<string> getAllFileList()
{
    #ifdef _WIN32
    const char *lsall   = "dir /s /B";
    const char *getbase = "echo %cd%";
    #else
    const char *lsall   = "find `pwd` -type f";
    const char *getbase = "pwd";
    #endif
    const string base(exec(getbase));
    stringstream ss(exec(lsall));
    string row;
    vector<string> res;

    while( getline(ss,row) )
    {
        string name = row.substr(base.size());
        if( isIgnored(name) ) 
        {
            continue;
        }
        res.emplace_back( name );
    }
    return res;
}

string toLatex(string s)
{
    string tmp = s;
    s.clear();
    for(char c:tmp){
        if( c=='_'||c=='&' )s.push_back('\\');
        s.push_back(c);
    }
    return s;
}

map<string,vector<pair<string,string>>> prepare(vector<string> files)
{
    // dirname => {filename, filepath}
    map<string,vector<pair<string,string>>>  codedata;
    auto dirname = [](string s){
        return s.substr(0,s.find('/'));
    };
    auto filename = [](string s){
        string tmp = s.substr(s.rfind('/')+1);
        return tmp.substr(0, tmp.size()-size_t(4));
    };
    
    for(string path:files)
    {
        replace(path.begin(), path.end(), '\\', '/');
        string dir  = toLatex(dirname(path));
        string file = toLatex(filename(path));

        codedata[dir].emplace_back(file, path);
    }
    return codedata;
}

void texCodeGen(ostream &out, map<string,vector<pair<string,string>>> files)
{
    auto sub = [](string s){return s.substr(s.size()-4);};
    for( auto package:files )
    {
        out<<"\\section{"<<package.first<<"}\n";
        for( auto p:package.second )
        {
            out<<"  \\"<<requireFile[sub(p.second)]<<"{"<<p.first<<"}{./"<<p.second<<"}\n";
        }
    }
}

int main()
{
    #ifdef _WIN32
    SetConsoleOutputCP(65001);
    #endif
    
    cout<<"[#] Start Processing Code Book List..."<<endl;
    cout<<"[1] Get Codes..."<<endl;
    auto files = getAllFileList();
    
    cout<<"    There are "<<files.size()<<" file(s)"<<endl;
    
    cout<<"[2] Prepare Codes..."<<endl;
    auto codes = prepare(files);
    
    cout<<"[3] Prepare Codes..."<<endl;
    ofstream fout("list.tex");
    texCodeGen(fout, codes);
    
    cout<<"[#] Done"<<endl;
}

