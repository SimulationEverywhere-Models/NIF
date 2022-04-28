/*******************************************************************
*
*  DESCRIPTION: class MainSimulator
*
*  AUTHOR:    Amir Barylko & Jorge Beyoglonian 
*  Version 2: Daniel A. Rodriguez
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*         mailto://drodrigu@dc.uba.ar
*
*  DATE: 27/6/1998
*  DATE: 12/6/1999 (v2)
*
*******************************************************************/

#ifndef __SIMULATOR_H
#define __SIMULATOR_H

/** include files **/
#include <iostream.h>
#include "root.h"          // EventList 
#include "ini.h"           // class Ini
#include "loader.h"        // class SimLoader 
#include "ltranadm.h"      // class LocalTransAdmin

/** forward declarations **/
class Model ;
class Coupled ;
class Atomic ;
class CoupledCell ;


/** declarations **/
class MainSimulator
{
public:
	static MainSimulator &Instance() ;
	MainSimulator &run() ;

	MainSimulator &loader( SimLoader *l )
			{sloader = l; return *this;}
	
	void registerNewAtomics() ;

	ostream &outputStream()
			{return loader()->outputStream();}

	ostream &logStream()
			{return loader()->logStream();}

	ostream &evalDebugStream()
			{return EvalDebug().Stream();}
			
	bool evalDebug()
			{return EvalDebug().Active();}
			
	bool existsParameter( const string &modelName, const string &parameterName ) const
			{return iniFile().exists( modelName, parameterName );}

	const string getParameter( const string &modelName, const string &parameterName ) const ;

	SimLoader *loader()
			{return sloader;}

private:
	friend class Coupled ;
	friend class Atomic ;

	// ** class variables ** //   
	static MainSimulator *instance ;

	// ** instance constants ** //
	const char separator ;
	const char *componentLabel ;
	const char *inPortsLabel ;
	const char *outPortsLabel ;
	const char *linksLabel ;

	// ** instance variables ** //
	Ini ini ;
	SimLoader *sloader ;

	// ** Methods ** //

	MainSimulator() ;
	MainSimulator &loadModels( istream&, bool printParserInfo ) ; 
	MainSimulator &loadExternalEvents( istream& ) ;
	MainSimulator &log( ostream & ) ;
	MainSimulator &output( ostream & ) ;
	MainSimulator &loadModel( Coupled &, Ini &, bool ) ;
	MainSimulator &loadPorts( Coupled &, Ini & ) ;
	MainSimulator &loadComponents( Coupled &, Ini &, bool ) ;
	MainSimulator &loadLinks( Coupled &, Ini & ) ;
	MainSimulator &loadCells( CoupledCell &, Ini &, bool ) ;
	MainSimulator &loadInitialCellValues( CoupledCell &, Ini & ) ;
	MainSimulator &loadInitialCellValuesFromFile( CoupledCell &parent, const string &fileName );
	MainSimulator &loadInitialCellValuesFromMapFile( CoupledCell &parent, const string &fileName );
	MainSimulator &loadDefaultTransitions( CoupledCell &, Ini &, bool ) ;
	MainSimulator &loadPortInTransitions( CoupledCell &, Ini &, bool ) ;
	MainSimulator &loadLocalZones( CoupledCell &, Ini &, bool ) ;

	MainSimulator &registerTransition(const LocalTransAdmin::Function &, Ini &, bool );
	MainSimulator &registerTransitionPortIn(const LocalTransAdmin::Function &, Ini &, bool, const string & );

	void showEvents( const EventList &events, ostream &out = cout ) ;

	Ini &iniFile()
			{return ini;}

	const Ini &iniFile() const
			{return ini;}
			
	bool splitString( const string &full, string &first, string &second, char separator );

};	// class MainSimulator

/** inline **/
inline
MainSimulator &MainSimulator::Instance()
{
	if( !instance )
		instance = new MainSimulator() ;

	return *instance ;
}

#endif   //__MainSimulator_H 
