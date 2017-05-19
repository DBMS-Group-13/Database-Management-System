#ifndef DATASTRUCTURE_H
#define DATASTRUCTURE_H
#pragma  once
#include <QDateTime>
// The definition of basic data types
typedef int INTEGER;			// Integer
typedef bool BOOLE;				// Boolean type
typedef double DOUBLE;			// Floating-point number
typedef char VARCHAR[256];		// String type
typedef QDateTime DATETIME;	// Date time type

// The definition of block structure

// Database block structure
struct DatabaseBlock{
    VARCHAR name;		// Database name
    BOOLE type;			// Database type：true is system database，false is custom database.
    VARCHAR filepath;	// Database file path
    DATETIME crtimAe;	// Creation time
};

// Table information structure
struct TableBlock
{
    VARCHAR name;		// Name
    INTEGER record_num;	// Record number
    INTEGER field_num;	// Field number
    VARCHAR tdf;		// Path of the table definition file
    VARCHAR trd;		// Path of the record file
    DATETIME crtime;	// Table creation time
    DATETIME mtime;		// Last modification time
};

// The definition of field block
struct FieldBlock
{
    VARCHAR name;		// Name
    INTEGER type;		// Type
    INTEGER param;		// Parameter
    DATETIME mtime;		// Last modification time
    INTEGER integrities;// Integrity constraints information
};
#endif // DATASTRUCTURE_H
