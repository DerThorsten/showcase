// everything needed for embedding
#include <pybind11/embed.h> 
#include <emscripten/bind.h>
#include <iostream>
#include <filesystem>



namespace py = pybind11;
namespace em = emscripten;

void embed_hello_world() 
{

    // start the interpreter and keep it alive
    py::scoped_interpreter guard{}; 

    // use the Python API
    py::print("Hello, World!"); 
}

void exec_code(const std::string & code)
{
    py::scoped_interpreter guard{};
    py::exec(code.c_str());
}


void set_pythonhome(const std::string & home)
{
    setenv("PYTHONHOME",home.c_str(),1); // does overwrite
}
void set_pythonpath(const std::string & path)
{
    setenv("PYTHONPATH",path.c_str(),1); // does overwrite
}

bool is_dir(const std::string & path)
{
    const std::filesystem::path fubar{path};
    return std::filesystem::is_directory(fubar);
}

void iter_dir(const std::string & path)
{

    const std::filesystem::path p{path};
    if(std::filesystem::is_directory(p))
    {

        std::cout<<"iterating "<<path<<":\n";
        for (auto const& dir_entry : std::filesystem::directory_iterator{p}) 
        {
            std::cout << dir_entry.path().string()<< '\n';
        }
    }
}

bool is_regular_file(const std::string & path)
{
    const std::filesystem::path fubar{path};
    return std::filesystem::is_regular_file(fubar);
}



EMSCRIPTEN_BINDINGS(my_module) {

    em::function("is_dir", &is_dir);
    em::function("iter_dir", &iter_dir);
    em::function("is_regular_file", &is_regular_file);

    em::function("set_pythonhome", &set_pythonhome);
    em::function("set_pythonpath", &set_pythonpath);

    em::function("exec_code", &exec_code);
    em::function("embed_hello_world", &embed_hello_world);
}