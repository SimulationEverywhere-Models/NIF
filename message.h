/*******************************************************************
*
*  DESCRIPTION: definitions of messages ( Y, *, D, X, I )
*
*  AUTHOR:    Amir Barylko & Jorge Beyoglonian 
*  Version 2: Daniel A. Rodriguez
*
*  EMAIL: mailto://amir@dc.uba.ar
*         mailto://jbeyoglo@dc.uba.ar
*         mailto://drodrigu@dc.uba.ar
*
*  DATE: 27/6/1998
*  DATE: 25/4/1999 (v2)
*
*******************************************************************/

#ifndef __MESSAGE_H
#define __MESSAGE_H

/** include files **/
#include "time.h"   	 // class Time
#include "value.h"  	 // class Value
#include "process.h"     // class Processor, ProcId
#include "procadm.h"	 // SingleProcessorAdmin
#include "port.h"
#include "strutil.h"

/** foward declarations **/
class Port  ;
class Processor ;

/** definitions **/
class Message
{
public:
	virtual ~Message()	//Destructor
		{}

	//** Queries **//
	const Time &time() const
		{return t;}
	
	const ProcId &procId() const
		{ return proc; }

	//** Modifiers **//
	Message &time( const Time &time )
		{ t = time; return *this; }

	Message &procId( const ProcId &p )
		{ proc = p; return *this; }

	virtual Message *clone() const = 0 ;

	virtual Message &sendTo( Processor & ) = 0 ;

	virtual const string type() const = 0 ;

	virtual const string asString() const
		{ return type() + " / " + time().asString() + " / " + SingleProcessorAdmin::Instance().processor( procId() ).asString(); }

protected:                                                
	Message( const Time &time, const ProcId &id )	// constructor
		: t(time)
		, proc(id)
		{}

	Message( const Message &msg)			// Copy constructor
		: t(msg.t)
		, proc(msg.proc)
		{}
	
	Message& operator=( const Message& );						 // Assignment operator
	int operator==( const Message& ) const;					 // Equality operator

private:
	Time t;
	ProcId proc;

};	// class Message



class InitMessage : public Message
{
public:
	InitMessage( const Time &tm, const ProcId &m)  // Default constructor
		:Message( tm, m)
		{}
	
	virtual Message *clone() const
		{ return new InitMessage(*this);}
		
	virtual Message &sendTo( Processor &proc )
		{ proc.receive(*this); return *this;}
		
	virtual const string type() const
	{return "I" ;}
};	// class InitMessage



class InternalMessage : public Message
{
public:
	InternalMessage( const Time &tm = Time::Zero, const ProcId &m = 0 )	//Default constructor
		:Message(tm,m)
		{}
		
	virtual Message *clone() const
		{return new InternalMessage(*this);}
	
	virtual Message &sendTo( Processor &proc )
		{proc.receive(*this); return *this;}

	virtual const string type() const
	{return "*" ;}

protected:
	InternalMessage& operator=(const InternalMessage&);			  //Assignment operator
	int operator==(const InternalMessage&) const;					  //Equality operator

private:

};	// class InternalMessage



class DoneMessage : public Message
{
public:
	DoneMessage();																			//Default constructor
	DoneMessage( const Time &tm, const ProcId &m, const Time &nextChange )
		:Message(tm,m)
		,next(nextChange)
		{}
	
	const Time &nextChange() const
		{return next;}
	
	Message &nextChange( const Time & );

	virtual Message *clone() const
		{return new DoneMessage(*this);}

	virtual Message &sendTo( Processor &proc )
		{proc.receive(*this); return *this;}

	virtual const string type() const
		{return "D" ;}
	
	virtual const string asString() const
		{ return Message::asString() + " / " + nextChange().asString(); }

protected:
	DoneMessage(const DoneMessage &msg)	  //Copy constructor
		:Message(msg)
		,next(msg.next)
		{}
	
	DoneMessage& operator=(const DoneMessage&);						  //Assignment operator
	int operator==(const DoneMessage&) const;							  //Equality operator

private:
	Time next;
};	// class DoneMessage



class ExternalMessage : public Message
{
public:
	ExternalMessage()
		:Message(Time::Zero, Processor::InvalidId)
		,p(NULL)
		,v(0)
		{}
	
	ExternalMessage( const Time &tm, const ProcId &m, const Port &port, const Value &val )
		:Message(tm,m)
		,p(&port)
		,v(val)
		{}

	ExternalMessage(const ExternalMessage &msg)	//Copy constructor
		:Message(msg)
		,p(msg.p)
		,v(msg.v)
		{}
		
	const Value &value() const
		{return v;}
		
	Message &value( const Value &val )
		{v=val; return *this;}

	const Port &port() const
		{assert(p); return *p;}

	Message &port( const Port &port )
		{p = &port; return *this;}

	virtual Message *clone() const
		{return new ExternalMessage(*this);}

	virtual Message &sendTo( Processor &proc )
		{proc.receive(*this); return *this;}

	virtual const string type() const
		{return "X" ;}

	virtual const string asString() const
		{ return Message::asString() + " / " + port().asString() + " / " + Value2StrReal(value()); }

protected:
	ExternalMessage& operator=(const ExternalMessage&);	//Assignment operator
	int operator==(const ExternalMessage&) const;	//Equality operator

private:
	const Port *p;
	Value v;

};	// class ExternalMessage



class OutputMessage : public Message
{
public:
	OutputMessage( const Time &tm, const ProcId &m, const Port &port, const Value &val )
		:Message(tm,m)
		,p(&port)
		,v(val)
		{}

	OutputMessage(const OutputMessage &msg)	//Copy constructor
		:Message(msg)
		,p(msg.p)
		,v(msg.v)
		{}
	
	const Value &value() const
		{return v;}
		
	Message &value( const Value &val )
		{v=val; return *this;}
		
	const Port &port() const
		{return *p;}
		
	Message &port( const Port &port )
		{p = &port; return *this;}
		
	virtual Message *clone() const
		{return new OutputMessage(*this);}

	virtual Message &sendTo( Processor &proc )
		{proc.receive(*this); return *this;}

	virtual const string type() const
		{return "Y" ;}

	virtual const string asString() const
		{ return Message::asString() + " / " + port().asString() + " / " + Value2StrReal(value()); }

protected:
	OutputMessage& operator=(const OutputMessage&);	  //Assignment operator
	int operator==(const OutputMessage&) const;	 //Equality operator

private:
	const Port *p;
	Value v;


};	// class OutputMessage

#endif   //__MESSAGE_H 
