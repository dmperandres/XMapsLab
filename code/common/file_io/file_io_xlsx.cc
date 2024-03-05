#include "file_io_xlsx.h"

using namespace QXlsx;

int _file_io_xlsx::open(const std::string &File_name1,_mode Mode)
{
    File_name=File_name1;

    if (Mode==_mode::MODE_READ){
        Table=new QXlsx::Document(QString::fromStdString(File_name));

        if (Table->load()) return 1;
    }
    else{
        Table=new QXlsx::Document();

        if (Table!=nullptr) return 1;
    }

    return 0;
}

/*************************************************************************/

std::string _file_io_xlsx::read_cell(int Row, int Col)
{
    QVariant Var;
    std::string Token;
    Cell* Cell;

    Cell=Table->cellAt(Row,Col);
    if (Cell!=nullptr){
        Var=Cell->readValue();
        Token=Var.toString().toStdString();
        Token.erase(std::remove(Token.begin(), Token.end(), ' '), Token.end());
    }
    return Token;
}

