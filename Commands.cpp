#include <sstream>
#include <sys/wait.h>
#include <iomanip>
#include "Commands.h"
#include <time.h>
#include <utime.h>
#include <unistd.h>

#include <sys/types.h>
#include <stdio.h>



using namespace std;

#if 0
#define FUNC_ENTRY()  \
  cout << __PRETTY_FUNCTION__ << " --> " << endl;

#define FUNC_EXIT()  \
  cout << __PRETTY_FUNCTION__ << " <-- " << endl;
#else
#define FUNC_ENTRY()
#define FUNC_EXIT()
#endif

const std::string WHITESPACE = " \n\r\t\f\v";

string _ltrim(const std::string& s)
{
  size_t start = s.find_first_not_of(WHITESPACE);
  return (start == std::string::npos) ? "" : s.substr(start);
}

string _rtrim(const std::string& s)
{
  size_t end = s.find_last_not_of(WHITESPACE);
  return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

string _trim(const std::string& s)
{
  return _rtrim(_ltrim(s));
}

vector<string> _parseCommandLine(const char* cmd_line) {
  FUNC_ENTRY()
  vector<string> args;
  std::istringstream iss(_trim(string(cmd_line)));
  for(std::string s; iss >> s; )
      args.push_back(s);
  return args;

  FUNC_EXIT()
}

bool _isBackgroundComamnd(const char* cmd_line) {
  const string str(cmd_line);
  return str[str.find_last_not_of(WHITESPACE)] == '&';
}

void _removeBackgroundSign(char* cmd_line) {
  const string str(cmd_line);
  // find last character other than spaces
  unsigned int idx = str.find_last_not_of(WHITESPACE);
  // if all characters are spaces then return
  if (idx == string::npos) {
    return;
  }
  // if the command line does not end with & then return
  if (cmd_line[idx] != '&') {
    return;
  }
  // replace the & (background sign) with space and then remove all tailing spaces.
  cmd_line[idx] = ' ';
  // truncate the command line string up to the last non-space character
  cmd_line[str.find_last_not_of(WHITESPACE, idx) + 1] = 0;
}

// TODO: Add your implementation for classes in Commands.h

SmallShell::~SmallShell() {
// TODO: add your implementation
}

/**
* Creates and returns a pointer to Command class which matches the given command line (cmd_line)
*/
Command * SmallShell::CreateCommand(const char *cmd_line, const std::vector<std::string> &args) {
	// For example:
/*
  string cmd_s = _trim(string(cmd_line));
  string firstWord = cmd_s.substr(0, cmd_s.find_first_of(" \n"));

  if (firstWord.compare("pwd") == 0) {
    return new GetCurrDirCommand(cmd_line);
  }
  else if (firstWord.compare("showpid") == 0) {
    return new ShowPidCommand(cmd_line);
  }
  else if ...
  .....
  else {
    return new ExternalCommand(cmd_line);
  }
  */
//    string cmd_s = _trim(string(cmd_line));
//    int index = cmd_s.find_first_of(" \n");
//    string firstWord = cmd_s.substr(0, index);
//    string secondWord;
//
//    string space = " ";
//    vector<string> parameters{};
//    int pos=0;
//    cmd_s.erase(0, index+1);
//    cmd_s = _trim(cmd_s);
//    while ((pos=cmd_s.find(space)) != (int)string::npos){
//        parameters.push_back(cmd_s.substr(0, pos));
//        cmd_s.erase(0, pos+1);
//        cmd_s = _trim(cmd_s);
//    }

    if (args[0] == "showpid") {
        return new ShowPidCommand(cmd_line);
    }

    if (args[0] == "pwd") {
        return new GetCurrDirCommand(cmd_line);
    }

  return nullptr;
}

void SmallShell::executeCommand(const char *cmd_line) {
  // for example:
  // Command* cmd = CreateCommand(cmd_line);
  // cmd->execute();
  // Please note that you must fork smash process for some commands (e.g., external commands....)

//    string cmd_s = _trim(string(cmd_line));
//    int index = cmd_s.find_first_of(" \n");
//    string firstWord = cmd_s.substr(0, index);
//    string secondWord;
//
//    string space = " ";
//    vector<string> parameters{};
//    int pos=0;
//    cmd_s.erase(0, index+1);
//    cmd_s = _trim(cmd_s);

//    while ((pos=cmd_s.find(space)) != (int)string::npos){
//        parameters.push_back(cmd_s.substr(0, pos));
//        cmd_s.erase(0, pos+1);
//        cmd_s = _trim(cmd_s);
//    }
    vector<string> args = _parseCommandLine(cmd_line);
    if (args.empty())
        return;

    if (args[0] == "chprompt") {
        if (args.size() > 1)
            setPromptMsg(args[1]);
        else
            setPromptMsg("smash");
    } else {
        Command* cmd = CreateCommand(cmd_line, args);
        if (cmd) {
            cmd->execute();
        }
        delete cmd;
    }
}

SmallShell::SmallShell() :prompt_msg("smash>"){
}

void SmallShell::setPromptMsg(string new_message){
    this->prompt_msg=new_message + ">";
}

std::string SmallShell::getPromptMsg(){
    return this->prompt_msg;
}

void ShowPidCommand::execute(){
    //todo: check in linux if it works
    std::cout << "smash pid is "<<getpid() << endl;
}

ShowPidCommand::ShowPidCommand(const char *cmd_line) : BuiltInCommand(cmd_line) {}

void GetCurrDirCommand::execute(){
    char* path = getcwd(nullptr, 0);
    if (path == nullptr) {
        //TODO ERROR HANDLING
    }
    std::cout << path << endl;
}

GetCurrDirCommand::GetCurrDirCommand(const char *cmd_line) : BuiltInCommand(cmd_line) {

}
