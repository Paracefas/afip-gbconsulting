#include <iostream>
#include "CSV.h"
#include <fstream>

void Clean(std::ifstream&, char const*);
std::string FormatDate(std::string);

int main(int argc, char const** argv)
{
    if(argc != 3) 
    {
        std::cerr << "[Error]: Usage afip.exe <source_file> <output_dir>\n";
        return 1;
    }
    std::string file_name = argv[1];
    std::string file_name_temp = file_name + "_temp.csv";
    std::ifstream source;
    source.open(file_name);
    Clean(source, file_name_temp.c_str()); 
    source.close();
    std::string file_name_out = file_name + "_out.sql";
    std::string file_path = argv[2];
    std::ofstream out;
    out.open(file_name_out);
    paracefas::CSV file{ file_name_temp };
    std::string mysql_query;
    std::cout << file.GetLineCount();
    for(int i = 0; i < 21386; ++i)
    {
        std::string fecha_deteccion = FormatDate(file.Get("Fecha_Deteccion", i)); 
        std::string fecha_publicacion = FormatDate(file.Get("Fecha_Publicacion", i)); 
        mysql_query = "insert into Terceros_Apocrifos (Fecha_Importacion,CUIT,Fecha_Deteccion,Fecha_Publicacion) select getdate(), " + std::string{"'"} + file.Get("CUIT", i) + "', '" + fecha_deteccion + "', '" + fecha_publicacion + "';";
        out << mysql_query << '\n';
    }
    out.close();
}
void Clean(std::ifstream& file, char const* output_name)
{
    if(!file.is_open()) return;
    std::ofstream out;
    out.open(output_name);
    std::string s;
    
    while( file >> s ) {
        out << s << '\n';
    }
    out.close();
}

std::string FormatDate(std::string date)
{
    size_t pos = date.find_last_of("/");
    std::string year = date.substr(pos+1);
    date.erase(date.begin() + pos, date.end());
    pos = date.find_last_of("/");
    std::string month = date.substr(pos+1);
    date.erase(date.begin() + pos, date.end());
    std::string day = date; 
    return year + month + day;
}