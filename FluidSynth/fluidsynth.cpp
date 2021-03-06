//-----------------------------------------------------------------------------
// Entaro ChucK Developer!
// This is a Chugin boilerplate, generated by chugerate!
//-----------------------------------------------------------------------------

// this should align with the correct versions of these ChucK files
#include "chuck_dl.h"
#include "chuck_def.h"

// general includes
#include <stdio.h>
#include <limits.h>

#include <fluidsynth.h>


template<typename T> T clamp(T value, T min, T max)
{
    if(value < min) return min;
    if(value > max) return max;
    return value;
}


// this is a special offset reserved for Chugin internal data
t_CKINT fluidsynth_data_offset = 0;


// class definition for internal Chugin data
// (note: this isn't strictly necessary, but serves as example
// of one recommended approach)
class fluidsynth
{
public:
    // constructor
    fluidsynth(t_CKFLOAT fs)
    {
        m_srate = fs;
        
        m_settings = new_fluid_settings();
        m_synth = new_fluid_synth(m_settings);
        
        fluid_synth_set_sample_rate(m_synth, m_srate);
    }
    
    ~fluidsynth()
    {
        delete_fluid_settings(m_settings);
        m_settings = NULL;
        delete_fluid_synth(m_synth);
        m_synth = NULL;
    }

    // for Chugins extending UGen
    void tick( SAMPLE *in, SAMPLE *out )
    {
        // default: this passes whatever input is patched into Chugin
        
        fluid_synth_write_float(m_synth, 1, out, 0, 0, out+1, 0, 0);
    }
    
    t_CKINT open(const std::string &sfont)
    {
        return fluid_synth_sfload(m_synth, sfont.c_str(), 1);
    }
    
    void noteOn(int chan, int key, int vel)
    {
        fluid_synth_noteon(m_synth, chan, key, vel);
    }
    
    void noteOff(int chan, int key)
    {
        fluid_synth_noteoff(m_synth, chan, key);
    }
    
private:
    // instance data
    t_CKFLOAT m_srate;
    
    fluid_settings_t *m_settings;
    fluid_synth_t *m_synth;
};



// implementation for the constructor
CK_DLL_CTOR(fluidsynth_ctor)
{
    // get the offset where we'll store our internal c++ class pointer
    OBJ_MEMBER_INT(SELF, fluidsynth_data_offset) = 0;
    
    // instantiate our internal c++ class representation
    fluidsynth * bcdata = new fluidsynth(API->vm->get_srate());
    
    // store the pointer in the ChucK object member
    OBJ_MEMBER_INT(SELF, fluidsynth_data_offset) = (t_CKINT) bcdata;
}


// implementation for the destructor
CK_DLL_DTOR(fluidsynth_dtor)
{
    // get our c++ class pointer
    fluidsynth * bcdata = (fluidsynth *) OBJ_MEMBER_INT(SELF, fluidsynth_data_offset);
    // check it
    if( bcdata )
    {
        // clean up
        delete bcdata;
        OBJ_MEMBER_INT(SELF, fluidsynth_data_offset) = 0;
        bcdata = NULL;
    }
}


// implementation for tick function
CK_DLL_TICKF(fluidsynth_tickf)
{
    // get our c++ class pointer
    fluidsynth * c = (fluidsynth *) OBJ_MEMBER_INT(SELF, fluidsynth_data_offset);
 
    // invoke our tick function; store in the magical out variable
    if(c) c->tick(in, out);

    // yes
    return TRUE;
}


// example implementation for setter
CK_DLL_MFUN(fluidsynth_open)
{
    fluidsynth * f_data = (fluidsynth *) OBJ_MEMBER_INT(SELF, fluidsynth_data_offset);
    
    Chuck_String * str = GET_NEXT_STRING(ARGS);
    
    RETURN->v_int = f_data->open(str->str);
}


// example implementation for getter
CK_DLL_MFUN(fluidsynth_noteOn)
{
    fluidsynth * f_data = (fluidsynth *) OBJ_MEMBER_INT(SELF, fluidsynth_data_offset);
    
    t_CKINT note = GET_NEXT_INT(ARGS);
    t_CKINT velocity = GET_NEXT_INT(ARGS);
    
    f_data->noteOn(0, note, velocity);
}

// example implementation for getter
CK_DLL_MFUN(fluidsynth_noteOff)
{
    fluidsynth * f_data = (fluidsynth *) OBJ_MEMBER_INT(SELF, fluidsynth_data_offset);
    
    t_CKINT note = GET_NEXT_INT(ARGS);
    
    f_data->noteOff(0, note);
}

// example implementation for getter
CK_DLL_MFUN(fluidsynth_noteOnChan)
{
    fluidsynth * f_data = (fluidsynth *) OBJ_MEMBER_INT(SELF, fluidsynth_data_offset);
    
    t_CKINT note = GET_NEXT_INT(ARGS);
    t_CKINT velocity = GET_NEXT_INT(ARGS);
    t_CKINT chan = GET_NEXT_INT(ARGS);
    
    f_data->noteOn(chan, note, velocity);
}

// example implementation for getter
CK_DLL_MFUN(fluidsynth_noteOffChan)
{
    fluidsynth * f_data = (fluidsynth *) OBJ_MEMBER_INT(SELF, fluidsynth_data_offset);
    
    t_CKINT note = GET_NEXT_INT(ARGS);
    t_CKINT chan = GET_NEXT_INT(ARGS);
    
    f_data->noteOff(chan, note);
}


// query function: chuck calls this when loading the Chugin
// NOTE: developer will need to modify this function to
// add additional functions to this Chugin
CK_DLL_QUERY( fluidsynth )
{
    QUERY->setname(QUERY, "FluidSynth");
    
    // begin the class definition
    QUERY->begin_class(QUERY, "FluidSynth", "UGen");

    QUERY->add_ctor(QUERY, fluidsynth_ctor);
    QUERY->add_dtor(QUERY, fluidsynth_dtor);
    
    QUERY->add_ugen_funcf(QUERY, fluidsynth_tickf, NULL, 0, 2);
    
    // NOTE: if this is to be a UGen with more than 1 channel, 
    // e.g., a multichannel UGen -- will need to use add_ugen_funcf()
    // and declare a tickf function using CK_DLL_TICKF

    QUERY->add_mfun(QUERY, fluidsynth_open, "int", "open");
    QUERY->add_arg(QUERY, "string", "file");
    
    QUERY->add_mfun(QUERY, fluidsynth_noteOn, "void", "noteOn");
    QUERY->add_arg(QUERY, "int", "note");
    QUERY->add_arg(QUERY, "int", "velocity");
    
    QUERY->add_mfun(QUERY, fluidsynth_noteOff, "void", "noteOff");
    QUERY->add_arg(QUERY, "int", "note");
    
    QUERY->add_mfun(QUERY, fluidsynth_noteOnChan, "void", "noteOn");
    QUERY->add_arg(QUERY, "int", "note");
    QUERY->add_arg(QUERY, "int", "velocity");
    QUERY->add_arg(QUERY, "int", "chan");
    
    QUERY->add_mfun(QUERY, fluidsynth_noteOffChan, "void", "noteOff");
    QUERY->add_arg(QUERY, "int", "note");
    QUERY->add_arg(QUERY, "int", "chan");
        
    fluidsynth_data_offset = QUERY->add_mvar(QUERY, "int", "@f_data", false);

    // IMPORTANT: this MUST be called!
    QUERY->end_class(QUERY);

    // wasn't that a breeze?
    return TRUE;
}


