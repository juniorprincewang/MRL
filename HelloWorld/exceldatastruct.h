#ifndef EXCELDATASTRUCT_H
#define EXCELDATASTRUCT_H

typedef struct data_struct
{
    QString regulator;
    QString chemical;
    QString crop;
    QString phi;
    QString rate;
    QVector<double> residues;
    QString unit;

} DataStruct;

#endif // EXCELDATASTRUCT_H
