//==============================================================================
///	
///	File: ScriptingRotateY.cpp
///	
/// Copyright (C) 2000-2014 by Smells Like Donkey Software Inc. All rights reserved.
///
/// This file is subject to the terms and conditions defined in
/// file 'LICENSE.txt', which is part of this source code package.
///	
//==============================================================================

#include "DT3Core/Scripting/ScriptingRotateY.hpp"
#include "DT3Core/System/Factory.hpp"
#include "DT3Core/System/Profiler.hpp"
#include "DT3Core/Types/FileBuffer/ArchiveData.hpp"
#include "DT3Core/Types/FileBuffer/Archive.hpp"

//==============================================================================
//==============================================================================

namespace DT3 {

//==============================================================================
/// Register with object factory
//==============================================================================

IMPLEMENT_FACTORY_CREATION_SCRIPT(ScriptingRotateY,"Math",NULL)
IMPLEMENT_PLUG_NODE(ScriptingRotateY)

IMPLEMENT_PLUG_INFO_INDEX(_in)
IMPLEMENT_PLUG_INFO_INDEX(_angle)
IMPLEMENT_PLUG_INFO_INDEX(_out)

//==============================================================================
//==============================================================================

BEGIN_IMPLEMENT_PLUGS(ScriptingRotateY)

	PLUG_INIT(_in,"In")
		.set_input(true)
		.affects(PLUG_INFO_INDEX(_out));
		
	PLUG_INIT(_angle,"Angle")
		.set_input(true)
		.affects(PLUG_INFO_INDEX(_out));

	PLUG_INIT(_out,"Out")
		.set_output(true);
        
END_IMPLEMENT_PLUGS

//==============================================================================
/// Standard class constructors/destructors
//==============================================================================

ScriptingRotateY::ScriptingRotateY (void)
    :   _in			(PLUG_INFO_INDEX(_in), Matrix3(	1.0F,0.0F,0.0F,
												0.0F,1.0F,0.0F,
												0.0F,0.0F,1.0F	)),
		_angle		(PLUG_INFO_INDEX(_angle), 0.0F),
		_out		(PLUG_INFO_INDEX(_out), Matrix3(	1.0F,0.0F,0.0F,
												0.0F,1.0F,0.0F,
												0.0F,0.0F,1.0F	))
{  

}
		
ScriptingRotateY::ScriptingRotateY (const ScriptingRotateY &rhs)
    :   ScriptingBase	(rhs),
		_in				(rhs._in),
		_angle			(rhs._angle),
		_out			(rhs._out)
{   

}

ScriptingRotateY & ScriptingRotateY::operator = (const ScriptingRotateY &rhs)
{
    // Make sure we are not assigning the class to itself
    if (&rhs != this) {        
		ScriptingBase::operator = (rhs);

		_in = rhs._in;
		_angle = rhs._angle;
		_out = rhs._out;
	}
    return (*this);
}
			
ScriptingRotateY::~ScriptingRotateY (void)
{

}

//==============================================================================
//==============================================================================

void ScriptingRotateY::initialize (void)
{
	ScriptingBase::initialize();
}

//==============================================================================
//==============================================================================

void ScriptingRotateY::archive (const std::shared_ptr<Archive> &archive)
{
    ScriptingBase::archive(archive);

	archive->push_domain (class_id ());
	        
	*archive << ARCHIVE_PLUG(_in, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_angle, DATA_PERSISTENT | DATA_SETTABLE);
	*archive << ARCHIVE_PLUG(_out, DATA_PERSISTENT);
													
    archive->pop_domain ();
}

//==============================================================================
//==============================================================================

DTboolean ScriptingRotateY::compute (const PlugBase *plug)
{
	PROFILER(SCRIPTING);

    if (super_type::compute(plug))  return true;

	if (plug == &_out) {	
		_out = Matrix3::set_rotation_y(_angle) * (_in);
		_out.set_clean();
		return true;
	}
	
	return false;
}

//==============================================================================
//==============================================================================

} // DT3

