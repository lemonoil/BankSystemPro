#pragma once
#include <libpq-fe.h>
#include <QString>
#include <QVector>
#include <QDebug>
#ifndef PSQL_H
#define PSQL_H
QVector<QString> SqlRes;


bool ExecSQL(const char* sql) {
    qDebug() << sql;
    PGconn* conLLCBC= PQconnectdb("host=47.100.92.240 dbname=bankaccount user=postgres password=lemonoil");
    if (PQstatus(conLLCBC) == CONNECTION_BAD) {
        fprintf(stderr, "Connection to database failed: %s\n",PQerrorMessage(conLLCBC));
        PQfinish(conLLCBC);
        return 0;
    }
    PGresult* res = NULL;
    QString tmp;
    SqlRes.clear();
    if (conLLCBC == NULL) {
        qDebug() << "Conn is null" << endl;
        PQfinish(conLLCBC);
        return false;
    }else{
        res = PQexec(const_cast<PGconn*>(conLLCBC), sql);
        if (res == NULL) return false;
        else{
            int tuple_num = PQntuples(res);
            int field_num = PQnfields(res);
            for (int i = 0; i < tuple_num; ++i) {
                for (int j = 0; j < field_num; ++j){
                    tmp = PQgetvalue(res, i, j);
                    if (!tmp.isEmpty()) {
                        qDebug() << tmp.toStdString().data();
                        SqlRes.push_back(tmp);
                    }
                }
                qDebug() << '\n' << endl;
            }
            PQfinish(conLLCBC);
            return true;
        }
    }
}
#endif //PSQL