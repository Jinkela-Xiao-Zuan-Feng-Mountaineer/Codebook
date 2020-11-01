import sys
from os import walk
from os.path import join, splitext

sys.stdin.reconfigure(encoding='utf-8')
sys.stdout.reconfigure(encoding='utf-8')

splitter = '\\' if sys.platform == "win32" else '/'

RequireOptionDict = {
    ".cpp": "includecpp",
    ".tex": "includetex"
}


def toLatex(string):
    string = string.replace('_', "\\_")
    string = string.replace('&', "\\&")
    return string


def replace(string):
    string = string.replace('\\', "/")
    return string


def PrepareFileDict(CurPath):
    FileDict = {}
    for root, _, files in walk(CurPath):
        for filename in files:
            fullpath = join(root, filename)
            name, file_extension = splitext(filename)
            if file_extension != ".cpp" and file_extension != ".tex":
                continue
            if fullpath[0:3] == "." + splitter + ".":
                continue
            if root == CurPath:
                continue
            DirName = toLatex(root[2:])
            if DirName not in FileDict:
                FileDict[DirName] = []
            FileDict[DirName].append(
                (file_extension, toLatex(name), replace(fullpath)))
    return FileDict


def texCodeGen(out, FileDict):
    for key in sorted(FileDict.keys()):
        out.write("\\section{" + key + "}\n")
        for (file_extension, name, path) in FileDict[key]:
            out.write(
                "  \\" + RequireOptionDict[file_extension] + "{" + name + "}{" + path + "}\n")


if __name__ == '__main__':
    print("[#] Start Processing Code Book List...")
    print("[1] Get Codes...")

    FileDict = PrepareFileDict(".")

    print("    There are", len(FileDict), "file(s)")
    print("[2] Prepare Codes...")
    with open('list.tex', 'w', encoding="utf-8") as fout:
        texCodeGen(fout, FileDict)
