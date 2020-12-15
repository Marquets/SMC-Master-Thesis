/* ------------------------------------------------------------
copyright: "(c)Romain Michon & John Granzow, CCRMA (Stanford University), GRAME, University of Michigan"
license: "MIT"
name: "modularInterpInstrMIDI", "ModularInterpInstrMidi"
Code generated with Faust 2.28.6 (https://faust.grame.fr)
Compilation options: -lang cpp -scal -ftz 0
------------------------------------------------------------ */

#ifndef  __mydsp_H__
#define  __mydsp_H__

/************************************************************************
 IMPORTANT NOTE : this file contains two clearly delimited sections :
 the ARCHITECTURE section (in two parts) and the USER section. Each section
 is governed by its own copyright and license. Please check individually
 each section for license and copyright information.
 *************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019-2020 GRAME, Centre National de Creation Musicale &
 Aalborg University (Copenhagen, Denmark)
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 
 ************************************************************************
 ************************************************************************/

#include "modularInterpInstrMIDI.h"

// IMPORTANT: in order for MapUI to work, the teensy linker must be g++
/************************** BEGIN MapUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MAPUI_H
#define FAUST_MAPUI_H

#include <vector>
#include <map>
#include <string>

/************************** BEGIN UI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __UI_H__
#define __UI_H__

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

/*******************************************************************************
 * UI : Faust DSP User Interface
 * User Interface as expected by the buildUserInterface() method of a DSP.
 * This abstract class contains only the method that the Faust compiler can
 * generate to describe a DSP user interface.
 ******************************************************************************/

struct Soundfile;

template <typename REAL>
struct UIReal
{
    UIReal() {}
    virtual ~UIReal() {}
    
    // -- widget's layouts
    
    virtual void openTabBox(const char* label) = 0;
    virtual void openHorizontalBox(const char* label) = 0;
    virtual void openVerticalBox(const char* label) = 0;
    virtual void closeBox() = 0;
    
    // -- active widgets
    
    virtual void addButton(const char* label, REAL* zone) = 0;
    virtual void addCheckButton(const char* label, REAL* zone) = 0;
    virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step) = 0;
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max) = 0;
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;
    
    // -- metadata declarations
    
    virtual void declare(REAL* zone, const char* key, const char* val) {}
};

struct UI : public UIReal<FAUSTFLOAT>
{
    UI() {}
    virtual ~UI() {}
};

#endif
/**************************  END  UI.h **************************/
/************************** BEGIN PathBuilder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_PATHBUILDER_H
#define FAUST_PATHBUILDER_H

#include <vector>
#include <string>
#include <algorithm>

/*******************************************************************************
 * PathBuilder : Faust User Interface
 * Helper class to build complete hierarchical path for UI items.
 ******************************************************************************/

class PathBuilder
{

    protected:
    
        std::vector<std::string> fControlsLevel;
       
    public:
    
        PathBuilder() {}
        virtual ~PathBuilder() {}
    
        std::string buildPath(const std::string& label) 
        {
            std::string res = "/";
            for (size_t i = 0; i < fControlsLevel.size(); i++) {
                res += fControlsLevel[i];
                res += "/";
            }
            res += label;
            std::replace(res.begin(), res.end(), ' ', '_');
            return res;
        }
    
        std::string buildLabel(std::string label)
        {
            std::replace(label.begin(), label.end(), ' ', '_');
            return label;
        }
    
        void pushLabel(const std::string& label) { fControlsLevel.push_back(label); }
        void popLabel() { fControlsLevel.pop_back(); }
    
};

#endif  // FAUST_PATHBUILDER_H
/**************************  END  PathBuilder.h **************************/

/*******************************************************************************
 * MapUI : Faust User Interface
 * This class creates a map of complete hierarchical path and zones for each UI items.
 ******************************************************************************/

class MapUI : public UI, public PathBuilder
{
    
    protected:
    
        // Complete path map
        std::map<std::string, FAUSTFLOAT*> fPathZoneMap;
    
        // Label zone map
        std::map<std::string, FAUSTFLOAT*> fLabelZoneMap;
    
    public:
        
        MapUI() {}
        virtual ~MapUI() {}
        
        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }
        
        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        
        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            fPathZoneMap[buildPath(label)] = zone;
            fLabelZoneMap[label] = zone;
        }
    
        // -- soundfiles
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
        
        // -- metadata declarations
        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {}
        
        // set/get
        void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                *fPathZoneMap[path] = value;
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                *fLabelZoneMap[path] = value;
            }
        }
        
        FAUSTFLOAT getParamValue(const std::string& path)
        {
            if (fPathZoneMap.find(path) != fPathZoneMap.end()) {
                return *fPathZoneMap[path];
            } else if (fLabelZoneMap.find(path) != fLabelZoneMap.end()) {
                return *fLabelZoneMap[path];
            } else {
                return FAUSTFLOAT(0);
            }
        }
    
        // map access 
        std::map<std::string, FAUSTFLOAT*>& getMap() { return fPathZoneMap; }
        
        int getParamsCount() { return int(fPathZoneMap.size()); }
        
        std::string getParamAddress(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return "";
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->first;
            }
        }
    
        std::string getParamAddress(FAUSTFLOAT* zone)
        {
            for (auto& it : fPathZoneMap) {
                if (it.second == zone) return it.first;
            }
            return "";
        }
    
        FAUSTFLOAT* getParamZone(const std::string& str)
        {
            if (fPathZoneMap.find(str) != fPathZoneMap.end()) {
                return fPathZoneMap[str];
            }
            if (fLabelZoneMap.find(str) != fLabelZoneMap.end()) {
                return fLabelZoneMap[str];
            }
            return nullptr;
        }
    
        FAUSTFLOAT* getParamZone(int index)
        {
            if (index < 0 || index > int(fPathZoneMap.size())) {
                return nullptr;
            } else {
                auto it = fPathZoneMap.begin();
                while (index-- > 0 && it++ != fPathZoneMap.end()) {}
                return it->second;
            }
        }
    
        static bool endsWith(const std::string& str, const std::string& end)
        {
            size_t l1 = str.length();
            size_t l2 = end.length();
            return (l1 >= l2) && (0 == str.compare(l1 - l2, l2, end));
        }
};


#endif // FAUST_MAPUI_H
/**************************  END  MapUI.h **************************/
/************************** BEGIN meta.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __meta__
#define __meta__

struct Meta
{
    virtual ~Meta() {};
    virtual void declare(const char* key, const char* value) = 0;
    
};

#endif
/**************************  END  meta.h **************************/
/************************** BEGIN dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp__
#define __dsp__

#include <string>
#include <vector>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct UI;
struct Meta;

/**
 * DSP memory manager.
 */

struct dsp_memory_manager {
    
    virtual ~dsp_memory_manager() {}
    
    virtual void* allocate(size_t size) = 0;
    virtual void destroy(void* ptr) = 0;
    
};

/**
* Signal processor definition.
*/

class dsp {

    public:

        dsp() {}
        virtual ~dsp() {}

        /* Return instance number of audio inputs */
        virtual int getNumInputs() = 0;
    
        /* Return instance number of audio outputs */
        virtual int getNumOutputs() = 0;
    
        /**
         * Trigger the ui_interface parameter with instance specific calls
         * to 'openTabBox', 'addButton', 'addVerticalSlider'... in order to build the UI.
         *
         * @param ui_interface - the user interface builder
         */
        virtual void buildUserInterface(UI* ui_interface) = 0;
    
        /* Returns the sample rate currently used by the instance */
        virtual int getSampleRate() = 0;
    
        /**
         * Global init, calls the following methods:
         * - static class 'classInit': static tables initialization
         * - 'instanceInit': constants and instance state initialization
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void init(int sample_rate) = 0;

        /**
         * Init instance state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceInit(int sample_rate) = 0;

        /**
         * Init instance constant state
         *
         * @param sample_rate - the sampling rate in Hertz
         */
        virtual void instanceConstants(int sample_rate) = 0;
    
        /* Init default control parameters values */
        virtual void instanceResetUserInterface() = 0;
    
        /* Init instance state (delay lines...) */
        virtual void instanceClear() = 0;
 
        /**
         * Return a clone of the instance.
         *
         * @return a copy of the instance on success, otherwise a null pointer.
         */
        virtual dsp* clone() = 0;
    
        /**
         * Trigger the Meta* parameter with instance specific calls to 'declare' (key, value) metadata.
         *
         * @param m - the Meta* meta user
         */
        virtual void metadata(Meta* m) = 0;
    
        /**
         * DSP instance computation, to be called with successive in/out audio buffers.
         *
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (eiher float, double or quad)
         *
         */
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) = 0;
    
        /**
         * DSP instance computation: alternative method to be used by subclasses.
         *
         * @param date_usec - the timestamp in microsec given by audio driver.
         * @param count - the number of frames to compute
         * @param inputs - the input audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         * @param outputs - the output audio buffers as an array of non-interleaved FAUSTFLOAT samples (either float, double or quad)
         *
         */
        virtual void compute(double /*date_usec*/, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }
       
};

/**
 * Generic DSP decorator.
 */

class decorator_dsp : public dsp {

    protected:

        dsp* fDSP;

    public:

        decorator_dsp(dsp* dsp = nullptr):fDSP(dsp) {}
        virtual ~decorator_dsp() { delete fDSP; }

        virtual int getNumInputs() { return fDSP->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP->getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { fDSP->buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return fDSP->getSampleRate(); }
        virtual void init(int sample_rate) { fDSP->init(sample_rate); }
        virtual void instanceInit(int sample_rate) { fDSP->instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { fDSP->instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { fDSP->instanceResetUserInterface(); }
        virtual void instanceClear() { fDSP->instanceClear(); }
        virtual decorator_dsp* clone() { return new decorator_dsp(fDSP->clone()); }
        virtual void metadata(Meta* m) { fDSP->metadata(m); }
        // Beware: subclasses usually have to overload the two 'compute' methods
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(count, inputs, outputs); }
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { fDSP->compute(date_usec, count, inputs, outputs); }
    
};

/**
 * DSP factory class.
 */

class dsp_factory {
    
    protected:
    
        // So that to force sub-classes to use deleteDSPFactory(dsp_factory* factory);
        virtual ~dsp_factory() {}
    
    public:
    
        virtual std::string getName() = 0;
        virtual std::string getSHAKey() = 0;
        virtual std::string getDSPCode() = 0;
        virtual std::string getCompileOptions() = 0;
        virtual std::vector<std::string> getLibraryList() = 0;
        virtual std::vector<std::string> getIncludePathnames() = 0;
    
        virtual dsp* createDSPInstance() = 0;
    
        virtual void setMemoryManager(dsp_memory_manager* manager) = 0;
        virtual dsp_memory_manager* getMemoryManager() = 0;
    
};

/**
 * On Intel set FZ (Flush to Zero) and DAZ (Denormals Are Zero)
 * flags to avoid costly denormals.
 */

#ifdef __SSE__
    #include <xmmintrin.h>
    #ifdef __SSE2__
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8040)
    #else
        #define AVOIDDENORMALS _mm_setcsr(_mm_getcsr() | 0x8000)
    #endif
#else
    #define AVOIDDENORMALS
#endif

#endif
/**************************  END  dsp.h **************************/

// MIDI support
#if MIDICTRL
/************************** BEGIN MidiUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef FAUST_MIDIUI_H
#define FAUST_MIDIUI_H

#include <vector>
#include <string>
#include <utility>
#include <iostream>
#include <cstdlib>
#include <cmath>

/************************** BEGIN GUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef __GUI_H__
#define __GUI_H__

#include <list>
#include <map>
#include <vector>
#include <iostream>
#include <assert.h>

#ifdef _WIN32
# pragma warning (disable: 4100)
#else
# pragma GCC diagnostic ignored "-Wunused-parameter"
#endif

/************************** BEGIN ValueConverter.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __ValueConverter__
#define __ValueConverter__

/***************************************************************************************
								ValueConverter.h
                            (GRAME, Copyright 2015-2019)

Set of conversion objects used to map user interface values (for example a gui slider
delivering values between 0 and 1) to faust values (for example a vslider between
20 and 20000) using a log scale.

-- Utilities

Range(lo,hi) : clip a value x between lo and hi
Interpolator(lo,hi,v1,v2) : Maps a value x between lo and hi to a value y between v1 and v2
Interpolator3pt(lo,mi,hi,v1,vm,v2) : Map values between lo mid hi to values between v1 vm v2

-- Value Converters

ValueConverter::ui2faust(x)
ValueConverter::faust2ui(x)

-- ValueConverters used for sliders depending of the scale

LinearValueConverter(umin, umax, fmin, fmax)
LinearValueConverter2(lo, mi, hi, v1, vm, v2) using 2 segments
LogValueConverter(umin, umax, fmin, fmax)
ExpValueConverter(umin, umax, fmin, fmax)

-- ValueConverters used for accelerometers based on 3 points

AccUpConverter(amin, amid, amax, fmin, fmid, fmax)		-- curve 0
AccDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 1
AccUpDownConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 2
AccDownUpConverter(amin, amid, amax, fmin, fmid, fmax)	-- curve 3

-- lists of ZoneControl are used to implement accelerometers metadata for each axes

ZoneControl(zone, valueConverter) : a zone with an accelerometer data converter

-- ZoneReader are used to implement screencolor metadata

ZoneReader(zone, valueConverter) : a zone with a data converter

****************************************************************************************/

#include <float.h>
#include <algorithm>    // std::max
#include <cmath>
#include <vector>
#include <assert.h>

//--------------------------------------------------------------------------------------
// Interpolator(lo,hi,v1,v2)
// Maps a value x between lo and hi to a value y between v1 and v2
// y = v1 + (x-lo)/(hi-lo)*(v2-v1)
// y = v1 + (x-lo) * coef   		with coef = (v2-v1)/(hi-lo)
// y = v1 + x*coef - lo*coef
// y = v1 - lo*coef + x*coef
// y = offset + x*coef				with offset = v1 - lo*coef
//--------------------------------------------------------------------------------------
class Interpolator
{
    private:

        //--------------------------------------------------------------------------------------
        // Range(lo,hi) clip a value between lo and hi
        //--------------------------------------------------------------------------------------
        struct Range
        {
            double fLo;
            double fHi;

            Range(double x, double y) : fLo(std::min<double>(x,y)), fHi(std::max<double>(x,y)) {}
            double operator()(double x) { return (x<fLo) ? fLo : (x>fHi) ? fHi : x; }
        };


        Range fRange;
        double fCoef;
        double fOffset;

    public:

        Interpolator(double lo, double hi, double v1, double v2) : fRange(lo,hi)
        {
            if (hi != lo) {
                // regular case
                fCoef = (v2-v1)/(hi-lo);
                fOffset = v1 - lo*fCoef;
            } else {
                // degenerate case, avoids division by zero
                fCoef = 0;
                fOffset = (v1+v2)/2;
            }
        }
        double operator()(double v)
        {
            double x = fRange(v);
            return  fOffset + x*fCoef;
        }

        void getLowHigh(double& amin, double& amax)
        {
            amin = fRange.fLo;
            amax = fRange.fHi;
        }
};

//--------------------------------------------------------------------------------------
// Interpolator3pt(lo,mi,hi,v1,vm,v2)
// Map values between lo mid hi to values between v1 vm v2
//--------------------------------------------------------------------------------------
class Interpolator3pt
{

    private:

        Interpolator fSegment1;
        Interpolator fSegment2;
        double fMid;

    public:

        Interpolator3pt(double lo, double mi, double hi, double v1, double vm, double v2) :
            fSegment1(lo, mi, v1, vm),
            fSegment2(mi, hi, vm, v2),
            fMid(mi) {}
        double operator()(double x) { return  (x < fMid) ? fSegment1(x) : fSegment2(x); }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fSegment1.getLowHigh(amin, amid);
            fSegment2.getLowHigh(amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Abstract ValueConverter class. Converts values between UI and Faust representations
//--------------------------------------------------------------------------------------
class ValueConverter
{

    public:

        virtual ~ValueConverter() {}
        virtual double ui2faust(double x) = 0;
        virtual double faust2ui(double x) = 0;
};

//--------------------------------------------------------------------------------------
// A converter than can be updated
//--------------------------------------------------------------------------------------

class UpdatableValueConverter : public ValueConverter {
    
    protected:
        
        bool fActive;
        
    public:
        
        UpdatableValueConverter():fActive(true)
        {}
        virtual ~UpdatableValueConverter()
        {}
        
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max) = 0;
        virtual void getMappingValues(double& amin, double& amid, double& amax) = 0;
        
        void setActive(bool on_off) { fActive = on_off; }
        bool getActive() { return fActive; }
    
};


//--------------------------------------------------------------------------------------
// Linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter : public ValueConverter
{
    
    private:
        
        Interpolator fUI2F;
        Interpolator fF2UI;
        
    public:
        
        LinearValueConverter(double umin, double umax, double fmin, double fmax) :
            fUI2F(umin,umax,fmin,fmax), fF2UI(fmin,fmax,umin,umax)
        {}
        
        LinearValueConverter() : fUI2F(0.,0.,0.,0.), fF2UI(0.,0.,0.,0.)
        {}
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
};

//--------------------------------------------------------------------------------------
// Two segments linear conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LinearValueConverter2 : public UpdatableValueConverter
{
    
    private:
    
        Interpolator3pt fUI2F;
        Interpolator3pt fF2UI;
        
    public:
    
        LinearValueConverter2(double amin, double amid, double amax, double min, double init, double max) :
            fUI2F(amin, amid, amax, min, init, max), fF2UI(min, init, max, amin, amid, amax)
        {}
        
        LinearValueConverter2() : fUI2F(0.,0.,0.,0.,0.,0.), fF2UI(0.,0.,0.,0.,0.,0.)
        {}
    
        virtual double ui2faust(double x) { return fUI2F(x); }
        virtual double faust2ui(double x) { return fF2UI(x); }
    
        virtual void setMappingValues(double amin, double amid, double amax, double min, double init, double max)
        {
            fUI2F = Interpolator3pt(amin, amid, amax, min, init, max);
            fF2UI = Interpolator3pt(min, init, max, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fUI2F.getMappingValues(amin, amid, amax);
        }
    
};

//--------------------------------------------------------------------------------------
// Logarithmic conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class LogValueConverter : public LinearValueConverter
{

    public:

        LogValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::log(std::max<double>(DBL_MIN, fmin)), std::log(std::max<double>(DBL_MIN, fmax)))
        {}

        virtual double ui2faust(double x) { return std::exp(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::log(std::max<double>(x, DBL_MIN))); }

};

//--------------------------------------------------------------------------------------
// Exponential conversion between ui and Faust values
//--------------------------------------------------------------------------------------
class ExpValueConverter : public LinearValueConverter
{

    public:

        ExpValueConverter(double umin, double umax, double fmin, double fmax) :
            LinearValueConverter(umin, umax, std::min<double>(DBL_MAX, std::exp(fmin)), std::min<double>(DBL_MAX, std::exp(fmax)))
        {}

        virtual double ui2faust(double x) { return std::log(LinearValueConverter::ui2faust(x)); }
        virtual double faust2ui(double x) { return LinearValueConverter::faust2ui(std::min<double>(DBL_MAX, std::exp(x))); }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up curve (curve 0)
//--------------------------------------------------------------------------------------
class AccUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt fA2F;
        Interpolator3pt fF2A;

    public:

        AccUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmid,fmax),
            fF2A(fmin,fmid,fmax,amin,amid,amax)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmid, fmax);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amin, amid, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }

};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down curve (curve 1)
//--------------------------------------------------------------------------------------
class AccDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator3pt	fF2A;

    public:

        AccDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmid,fmin),
            fF2A(fmin,fmid,fmax,amax,amid,amin)
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
             //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmid, fmin);
            fF2A = Interpolator3pt(fmin, fmid, fmax, amax, amid, amin);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using an Up-Down curve (curve 2)
//--------------------------------------------------------------------------------------
class AccUpDownConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccUpDownConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmin,fmax,fmin),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccUpDownConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmin, fmax, fmin);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Convert accelerometer or gyroscope values to Faust values
// Using a Down-Up curve (curve 3)
//--------------------------------------------------------------------------------------
class AccDownUpConverter : public UpdatableValueConverter
{

    private:

        Interpolator3pt	fA2F;
        Interpolator fF2A;

    public:

        AccDownUpConverter(double amin, double amid, double amax, double fmin, double fmid, double fmax) :
            fA2F(amin,amid,amax,fmax,fmin,fmax),
            fF2A(fmin,fmax,amin,amax)				// Special, pseudo inverse of a non monotonic function
        {}

        virtual double ui2faust(double x) { return fA2F(x); }
        virtual double faust2ui(double x) { return fF2A(x); }

        virtual void setMappingValues(double amin, double amid, double amax, double fmin, double fmid, double fmax)
        {
            //__android_log_print(ANDROID_LOG_ERROR, "Faust", "AccDownUpConverter update %f %f %f %f %f %f", amin,amid,amax,fmin,fmid,fmax);
            fA2F = Interpolator3pt(amin, amid, amax, fmax, fmin, fmax);
            fF2A = Interpolator(fmin, fmax, amin, amax);
        }

        virtual void getMappingValues(double& amin, double& amid, double& amax)
        {
            fA2F.getMappingValues(amin, amid, amax);
        }
};

//--------------------------------------------------------------------------------------
// Base class for ZoneControl
//--------------------------------------------------------------------------------------
class ZoneControl
{

    protected:

        FAUSTFLOAT*	fZone;

    public:

        ZoneControl(FAUSTFLOAT* zone) : fZone(zone) {}
        virtual ~ZoneControl() {}

        virtual void update(double v) const {}

        virtual void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max) {}
        virtual void getMappingValues(double& amin, double& amid, double& amax) {}

        FAUSTFLOAT* getZone() { return fZone; }

        virtual void setActive(bool on_off) {}
        virtual bool getActive() { return false; }

        virtual int getCurve() { return -1; }

};

//--------------------------------------------------------------------------------------
//  Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class ConverterZoneControl : public ZoneControl
{

    protected:

        ValueConverter* fValueConverter;

    public:

        ConverterZoneControl(FAUSTFLOAT* zone, ValueConverter* converter) : ZoneControl(zone), fValueConverter(converter) {}
        virtual ~ConverterZoneControl() { delete fValueConverter; } // Assuming fValueConverter is not kept elsewhere...

        virtual void update(double v) const { *fZone = fValueConverter->ui2faust(v); }

        ValueConverter* getConverter() { return fValueConverter; }

};

//--------------------------------------------------------------------------------------
// Association of a zone and a four value converter, each one for each possible curve.
// Useful to implement accelerometers metadata as a list of ZoneControl for each axes
//--------------------------------------------------------------------------------------
class CurveZoneControl : public ZoneControl
{

    private:

        std::vector<UpdatableValueConverter*> fValueConverters;
        int fCurve;

    public:

        CurveZoneControl(FAUSTFLOAT* zone, int curve, double amin, double amid, double amax, double min, double init, double max) : ZoneControl(zone), fCurve(0)
        {
            assert(curve >= 0 && curve <= 3);
            fValueConverters.push_back(new AccUpConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccUpDownConverter(amin, amid, amax, min, init, max));
            fValueConverters.push_back(new AccDownUpConverter(amin, amid, amax, min, init, max));
            fCurve = curve;
        }
        virtual ~CurveZoneControl()
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                delete(*it);
            }
        }
        void update(double v) const { if (fValueConverters[fCurve]->getActive()) *fZone = fValueConverters[fCurve]->ui2faust(v); }

        void setMappingValues(int curve, double amin, double amid, double amax, double min, double init, double max)
        {
            fValueConverters[curve]->setMappingValues(amin, amid, amax, min, init, max);
            fCurve = curve;
        }

        void getMappingValues(double& amin, double& amid, double& amax)
        {
            fValueConverters[fCurve]->getMappingValues(amin, amid, amax);
        }

        void setActive(bool on_off)
        {
            std::vector<UpdatableValueConverter*>::iterator it;
            for (it = fValueConverters.begin(); it != fValueConverters.end(); it++) {
                (*it)->setActive(on_off);
            }
        }

        int getCurve() { return fCurve; }
};

class ZoneReader
{

    private:

        FAUSTFLOAT* fZone;
        Interpolator fInterpolator;

    public:

        ZoneReader(FAUSTFLOAT* zone, double lo, double hi) : fZone(zone), fInterpolator(lo, hi, 0, 255) {}

        virtual ~ZoneReader() {}

        int getValue()
        {
            return (fZone != nullptr) ? int(fInterpolator(*fZone)) : 127;
        }

};

#endif
/**************************  END  ValueConverter.h **************************/
/************************** BEGIN MetaDataUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef MetaData_UI_H
#define MetaData_UI_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <map>
#include <set>
#include <string>
#include <string.h>
#include <assert.h>

/************************** BEGIN SimpleParser.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef SIMPLEPARSER_H
#define SIMPLEPARSER_H

// ---------------------------------------------------------------------
//                          Simple Parser
// A parser returns true if it was able to parse what it is
// supposed to parse and advance the pointer. Otherwise it returns false
// and the pointer is not advanced so that another parser can be tried.
// ---------------------------------------------------------------------

#include <vector>
#include <map>
#include <string>
#include <cmath>
#include <iostream>
#include <ctype.h>

#ifndef _WIN32
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

struct itemInfo {
    std::string type;
    std::string label;
    std::string url;
    std::string address;
    int index;
    double init;
    double fmin;
    double fmax;
    double step;
    std::vector<std::pair<std::string, std::string> > meta;
    
    itemInfo():index(0), init(0.), fmin(0.), fmax(0.), step(0.)
    {}
};

// ---------------------------------------------------------------------
//                          Elementary parsers
// ---------------------------------------------------------------------

// Report a parsing error
static bool parseError(const char*& p, const char* errmsg)
{
    std::cerr << "Parse error : " << errmsg << " here : " << p << std::endl;
    return true;
}

/**
 * @brief skipBlank : advance pointer p to the first non blank character
 * @param p the string to parse, then the remaining string
 */
static void skipBlank(const char*& p)
{
    while (isspace(*p)) { p++; }
}

// Parse character x, but don't report error if fails
static bool tryChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseChar : parse a specific character x
 * @param p the string to parse, then the remaining string
 * @param x the character to recognize
 * @return true if x was found at the begin of p
 */
static bool parseChar(const char*& p, char x)
{
    skipBlank(p);
    if (x == *p) {
        p++;
        return true;
    } else {
        return false;
    }
}

/**
 * @brief parseWord : parse a specific string w
 * @param p the string to parse, then the remaining string
 * @param w the string to recognize
 * @return true if string w was found at the begin of p
 */
static bool parseWord(const char*& p, const char* w)
{
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    while ((*w == *p) && (*w)) {++w; ++p;}
    if (*w) {
        p = saved;
        return false;
    } else {
        return true;
    }
}

/**
 * @brief parseDouble : parse number [s]dddd[.dddd] or [s]d[.dddd][E|e][s][dddd] and store the result in x
 * @param p the string to parse, then the remaining string
 * @param x the float number found if any
 * @return true if a float number was found at the begin of p
 */
static bool parseDouble(const char*& p, double& x)
{
    double sign = 1.0;     // sign of the number
    double ipart = 0;      // integral part of the number
    double dpart = 0;      // decimal part of the number before division
    double dcoef = 1.0;    // division factor for the decimal part
    double expsign = 1.0;  // sign of the E|e part
    double expcoef = 0.0;  // multiplication factor of E|e part
    
    bool valid = false;    // true if the number contains at least one digit
    
    skipBlank(p);
    const char* saved = p;  // to restore position if we fail
    
    // Sign
    if (parseChar(p, '+')) {
        sign = 1.0;
    } else if (parseChar(p, '-')) {
        sign = -1.0;
    }
    
    // Integral part
    while (isdigit(*p)) {
        valid = true;
        ipart = ipart*10 + (*p - '0');
        p++;
    }
    
    // Possible decimal part
    if (parseChar(p, '.')) {
        while (isdigit(*p)) {
            valid = true;
            dpart = dpart*10 + (*p - '0');
            dcoef *= 10.0;
            p++;
        }
    }
    
    // Possible E|e part
    if (parseChar(p, 'E') || parseChar(p, 'e')) {
        if (parseChar(p, '+')) {
            expsign = 1.0;
        } else if (parseChar(p, '-')) {
            expsign = -1.0;
        }
        while (isdigit(*p)) {
            expcoef = expcoef*10 + (*p - '0');
            p++;
        }
    }
    
    if (valid)  {
        x = (sign*(ipart + dpart/dcoef)) * std::pow(10.0, expcoef*expsign);
    } else {
        p = saved;
    }
    return valid;
}

/**
 * @brief parseString, parse an arbitrary quoted string q...q and store the result in s
 * @param p the string to parse, then the remaining string
 * @param quote the character used to quote the string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseString(const char*& p, char quote, std::string& s)
{
    std::string str;
    skipBlank(p);
    
    const char* saved = p;  // to restore position if we fail
    if (*p++ == quote) {
        while ((*p != 0) && (*p != quote)) {
            str += *p++;
        }
        if (*p++ == quote) {
            s = str;
            return true;
        }
    }
    p = saved;
    return false;
}

/**
 * @brief parseSQString, parse a single quoted string '...' and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseSQString(const char*& p, std::string& s)
{
    return parseString(p, '\'', s);
}

/**
 * @brief parseDQString, parse a double quoted string "..." and store the result in s
 * @param p the string to parse, then the remaining string
 * @param s the (unquoted) string found if any
 * @return true if a string was found at the begin of p
 */
static bool parseDQString(const char*& p, std::string& s)
{
    return parseString(p, '"', s);
}

// ---------------------------------------------------------------------
//
//                          IMPLEMENTATION
// 
// ---------------------------------------------------------------------

/**
 * @brief parseMenuItem, parse a menu item ...'low':440.0...
 * @param p the string to parse, then the remaining string
 * @param name the name found
 * @param value the value found
 * @return true if a nemu item was found
 */
static bool parseMenuItem(const char*& p, std::string& name, double& value)
{
    const char* saved = p;  // to restore position if we fail
    if (parseSQString(p, name) && parseChar(p, ':') && parseDouble(p, value)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

static bool parseMenuItem2(const char*& p, std::string& name)
{
    const char* saved = p;  // to restore position if we fail
    // single quoted
    if (parseSQString(p, name)) {
        return true;
    } else {
        p = saved;
        return false;
    }
}

/**
 * @brief parseMenuList, parse a menu list {'low' : 440.0; 'mid' : 880.0; 'hi' : 1760.0}...
 * @param p the string to parse, then the remaining string
 * @param names the vector of names found
 * @param values the vector of values found
 * @return true if a menu list was found
 */
static bool parseMenuList(const char*& p, std::vector<std::string>& names, std::vector<double>& values)
{
    std::vector<std::string> tmpnames;
    std::vector<double> tmpvalues;
    const char* saved = p; // to restore position if we fail

    if (parseChar(p, '{')) {
        do {
            std::string n;
            double v;
            if (parseMenuItem(p, n, v)) {
                tmpnames.push_back(n);
                tmpvalues.push_back(v);
            } else {
                p = saved;
                return false;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            values = tmpvalues;
            return true;
        }
    }
    p = saved;
    return false;
}

static bool parseMenuList2(const char*& p, std::vector<std::string>& names, bool debug)
{
    std::vector<std::string> tmpnames;
    const char* saved = p;  // to restore position if we fail
    
    if (parseChar(p, '{')) {
        do {
            std::string n;
            if (parseMenuItem2(p, n)) {
                tmpnames.push_back(n);
            } else {
                goto error;
            }
        } while (parseChar(p, ';'));
        if (parseChar(p, '}')) {
            // we suceeded
            names = tmpnames;
            return true;
        }
    }
    
error:
    if (debug) { std::cerr << "parseMenuList2 : (" << saved << ") is not a valid list !\n"; }
    p = saved;
    return false;
}

/// ---------------------------------------------------------------------
// Parse list of strings
/// ---------------------------------------------------------------------
static bool parseList(const char*& p, std::vector<std::string>& items)
{
    const char* saved = p;  // to restore position if we fail
    if (parseChar(p, '[')) {
        do {
            std::string item;
            if (!parseDQString(p, item)) {
                p = saved;
                return false;
            }
            items.push_back(item);
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseMetaData(const char*& p, std::map<std::string, std::string>& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas[metaKey] = metaValue;
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

static bool parseItemMetaData(const char*& p, std::vector<std::pair<std::string, std::string> >& metadatas)
{
    const char* saved = p; // to restore position if we fail
    std::string metaKey, metaValue;
    if (parseChar(p, ':') && parseChar(p, '[')) {
        do { 
            if (parseChar(p, '{') && parseDQString(p, metaKey) && parseChar(p, ':') && parseDQString(p, metaValue) && parseChar(p, '}')) {
                metadatas.push_back(std::make_pair(metaKey, metaValue));
            }
        } while (tryChar(p, ','));
        return parseChar(p, ']');
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse metadatas of the interface:
// "name" : "...", "inputs" : "...", "outputs" : "...", ...
// and store the result as key/value
/// ---------------------------------------------------------------------
static bool parseGlobalMetaData(const char*& p, std::string& key, std::string& value, double& dbl, std::map<std::string, std::string>& metadatas, std::vector<std::string>& items)
{
    const char* saved = p; // to restore position if we fail
    if (parseDQString(p, key)) {
        if (key == "meta") {
            return parseMetaData(p, metadatas);
        } else {
            return parseChar(p, ':') && (parseDQString(p, value) || parseList(p, items) || parseDouble(p, dbl));
        }
    } else {
        p = saved;
        return false;
    }
}

// ---------------------------------------------------------------------
// Parse gui:
// "type" : "...", "label" : "...", "address" : "...", ...
// and store the result in uiItems Vector
/// ---------------------------------------------------------------------
static bool parseUI(const char*& p, std::vector<itemInfo>& uiItems, int& numItems)
{
    const char* saved = p; // to restore position if we fail
    if (parseChar(p, '{')) {
   
        std::string label;
        std::string value;
        double dbl = 0;
        
        do {
            if (parseDQString(p, label)) {
                if (label == "type") {
                    if (uiItems.size() != 0) {
                        numItems++;
                    }
                    if (parseChar(p, ':') && parseDQString(p, value)) {   
                        itemInfo item;
                        item.type = value;
                        uiItems.push_back(item);
                    }
                }
                
                else if (label == "label") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].label = value;
                    }
                }
                
                else if (label == "url") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].url = value;
                    }
                }
                
                else if (label == "address") {
                    if (parseChar(p, ':') && parseDQString(p, value)) {
                        uiItems[numItems].address = value;
                    }
                }
                
                else if (label == "index") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].index = int(dbl);
                    }
                }
                
                else if (label == "meta") {
                    if (!parseItemMetaData(p, uiItems[numItems].meta)) {
                        return false;
                    }
                }
                
                else if (label == "init") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].init = dbl;
                    }
                }
                
                else if (label == "min") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmin = dbl;
                    }
                }
                
                else if (label == "max") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].fmax = dbl;
                    }
                }
                
                else if (label == "step") {
                    if (parseChar(p, ':') && parseDouble(p, dbl)) {
                        uiItems[numItems].step = dbl;
                    }
                }
                
                else if (label == "items") {
                    if (parseChar(p, ':') && parseChar(p, '[')) {
                        do {
                            if (!parseUI(p, uiItems, numItems)) {
                                p = saved;
                                return false;
                            }
                        } while (tryChar(p, ','));
                        if (parseChar(p, ']')) {
                            itemInfo item;
                            item.type = "close";
                            uiItems.push_back(item);
                            numItems++;
                        }
                    }
                }
            } else {
                p = saved;
                return false;
            }
            
        } while (tryChar(p, ','));
    
        return parseChar(p, '}');
    } else {
        return true; // "items": [] is valid
    }
}

// ---------------------------------------------------------------------
// Parse full JSON record describing a JSON/Faust interface :
// {"metadatas": "...", "ui": [{ "type": "...", "label": "...", "items": [...], "address": "...","init": "...", "min": "...", "max": "...","step": "..."}]}
//
// and store the result in map Metadatas and vector containing the items of the interface. Returns true if parsing was successfull.
/// ---------------------------------------------------------------------
static bool parseJson(const char*& p,
                      std::map<std::string, std::pair<std::string, double> >& metaDatas0,
                      std::map<std::string, std::string>& metaDatas1,
                      std::map<std::string, std::vector<std::string> >& metaDatas2,
                      std::vector<itemInfo>& uiItems)
{
    parseChar(p, '{');
    
    do {
        std::string key;
        std::string value;
        double dbl = 0;
        std::vector<std::string> items;
        if (parseGlobalMetaData(p, key, value, dbl, metaDatas1, items)) {
            if (key != "meta") {
                // keep "name", "inputs", "outputs" key/value pairs
                if (items.size() > 0) {
                    metaDatas2[key] = items;
                    items.clear();
                } else if (value != "") {
                    metaDatas0[key].first = value;
                } else {
                    metaDatas0[key].second = dbl;
                }
            }
        } else if (key == "ui") {
            int numItems = 0;
            parseChar(p, '[') && parseUI(p, uiItems, numItems);
        }
    } while (tryChar(p, ','));
    
    return parseChar(p, '}');
}

#endif // SIMPLEPARSER_H
/**************************  END  SimpleParser.h **************************/

static bool startWith(const std::string& str, const std::string& prefix)
{
    return (str.substr(0, prefix.size()) == prefix);
}

/**
 * Convert a dB value into a scale between 0 and 1 (following IEC standard ?)
 */
static FAUSTFLOAT dB2Scale(FAUSTFLOAT dB)
{
    FAUSTFLOAT scale = FAUSTFLOAT(1.0);
    
    /*if (dB < -70.0f)
     scale = 0.0f;
     else*/
    if (dB < FAUSTFLOAT(-60.0))
        scale = (dB + FAUSTFLOAT(70.0)) * FAUSTFLOAT(0.0025);
    else if (dB < FAUSTFLOAT(-50.0))
        scale = (dB + FAUSTFLOAT(60.0)) * FAUSTFLOAT(0.005) + FAUSTFLOAT(0.025);
    else if (dB < FAUSTFLOAT(-40.0))
        scale = (dB + FAUSTFLOAT(50.0)) * FAUSTFLOAT(0.0075) + FAUSTFLOAT(0.075);
    else if (dB < FAUSTFLOAT(-30.0))
        scale = (dB + FAUSTFLOAT(40.0)) * FAUSTFLOAT(0.015) + FAUSTFLOAT(0.15);
    else if (dB < FAUSTFLOAT(-20.0))
        scale = (dB + FAUSTFLOAT(30.0)) * FAUSTFLOAT(0.02) + FAUSTFLOAT(0.3);
    else if (dB < FAUSTFLOAT(-0.001) || dB > FAUSTFLOAT(0.001))  /* if (dB < 0.0) */
        scale = (dB + FAUSTFLOAT(20.0)) * FAUSTFLOAT(0.025) + FAUSTFLOAT(0.5);
    
    return scale;
}

/*******************************************************************************
 * MetaDataUI : Common class for MetaData handling
 ******************************************************************************/

//============================= BEGIN GROUP LABEL METADATA===========================
// Unlike widget's label, metadata inside group's label are not extracted directly by
// the Faust compiler. Therefore they must be extracted within the architecture file
//-----------------------------------------------------------------------------------

class MetaDataUI {
    
    protected:
        
        std::string                         fGroupTooltip;
        std::map<FAUSTFLOAT*, FAUSTFLOAT>   fGuiSize;            // map widget zone with widget size coef
        std::map<FAUSTFLOAT*, std::string>  fTooltip;            // map widget zone with tooltip strings
        std::map<FAUSTFLOAT*, std::string>  fUnit;               // map widget zone to unit string (i.e. "dB")
        std::map<FAUSTFLOAT*, std::string>  fRadioDescription;   // map zone to {'low':440; ...; 'hi':1000.0}
        std::map<FAUSTFLOAT*, std::string>  fMenuDescription;    // map zone to {'low':440; ...; 'hi':1000.0}
        std::set<FAUSTFLOAT*>               fKnobSet;            // set of widget zone to be knobs
        std::set<FAUSTFLOAT*>               fLedSet;             // set of widget zone to be LEDs
        std::set<FAUSTFLOAT*>               fNumSet;             // set of widget zone to be numerical bargraphs
        std::set<FAUSTFLOAT*>               fLogSet;             // set of widget zone having a log UI scale
        std::set<FAUSTFLOAT*>               fExpSet;             // set of widget zone having an exp UI scale
        std::set<FAUSTFLOAT*>               fHiddenSet;          // set of hidden widget zone
        
        void clearMetadata()
        {
            fGuiSize.clear();
            fTooltip.clear();
            fUnit.clear();
            fRadioDescription.clear();
            fMenuDescription.clear();
            fKnobSet.clear();
            fLedSet.clear();
            fNumSet.clear();
            fLogSet.clear();
            fExpSet.clear();
            fHiddenSet.clear();
            fGroupTooltip = "";
        }
        
        /**
         * rmWhiteSpaces(): Remove the leading and trailing white spaces of a string
         * (but not those in the middle of the string)
         */
        static std::string rmWhiteSpaces(const std::string& s)
        {
            size_t i = s.find_first_not_of(" \t");
            size_t j = s.find_last_not_of(" \t");
            if ((i != std::string::npos) && (j != std::string::npos)) {
                return s.substr(i, 1+j-i);
            } else {
                return "";
            }
        }
        
        /**
         * Format tooltip string by replacing some white spaces by
         * return characters so that line width doesn't exceed n.
         * Limitation : long words exceeding n are not cut
         */
        std::string formatTooltip(int n, const std::string& tt)
        {
            std::string ss = tt;  // ss string we are going to format
            int lws = 0;          // last white space encountered
            int lri = 0;          // last return inserted
            for (int i = 0; i < (int)tt.size(); i++) {
                if (tt[i] == ' ') lws = i;
                if (((i-lri) >= n) && (lws > lri)) {
                    // insert return here
                    ss[lws] = '\n';
                    lri = lws;
                }
            }
            return ss;
        }
        
    public:
        
        virtual ~MetaDataUI()
        {}
        
        enum Scale {
            kLin,
            kLog,
            kExp
        };
        
        Scale getScale(FAUSTFLOAT* zone)
        {
            if (fLogSet.count(zone) > 0) return kLog;
            if (fExpSet.count(zone) > 0) return kExp;
            return kLin;
        }
        
        bool isKnob(FAUSTFLOAT* zone)
        {
            return fKnobSet.count(zone) > 0;
        }
        
        bool isRadio(FAUSTFLOAT* zone)
        {
            return fRadioDescription.count(zone) > 0;
        }
        
        bool isMenu(FAUSTFLOAT* zone)
        {
            return fMenuDescription.count(zone) > 0;
        }
        
        bool isLed(FAUSTFLOAT* zone)
        {
            return fLedSet.count(zone) > 0;
        }
        
        bool isNumerical(FAUSTFLOAT* zone)
        {
            return fNumSet.count(zone) > 0;
        }
        
        bool isHidden(FAUSTFLOAT* zone)
        {
            return fHiddenSet.count(zone) > 0;
        }
        
        /**
         * Extracts metadata from a label : 'vol [unit: dB]' -> 'vol' + metadata(unit=dB)
         */
        static void extractMetadata(const std::string& fulllabel, std::string& label, std::map<std::string, std::string>& metadata)
        {
            enum {kLabel, kEscape1, kEscape2, kEscape3, kKey, kValue};
            int state = kLabel; int deep = 0;
            std::string key, value;
            
            for (unsigned int i = 0; i < fulllabel.size(); i++) {
                char c = fulllabel[i];
                switch (state) {
                    case kLabel :
                        assert(deep == 0);
                        switch (c) {
                            case '\\' : state = kEscape1; break;
                            case '[' : state = kKey; deep++; break;
                            default : label += c;
                        }
                        break;
                        
                    case kEscape1:
                        label += c;
                        state = kLabel;
                        break;
                        
                    case kEscape2:
                        key += c;
                        state = kKey;
                        break;
                        
                    case kEscape3:
                        value += c;
                        state = kValue;
                        break;
                        
                    case kKey:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape2;
                                break;
                                
                            case '[':
                                deep++;
                                key += c;
                                break;
                                
                            case ':':
                                if (deep == 1) {
                                    state = kValue;
                                } else {
                                    key += c;
                                }
                                break;
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = "";
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    key += c;
                                }
                                break;
                            default : key += c;
                        }
                        break;
                        
                    case kValue:
                        assert(deep > 0);
                        switch (c) {
                            case '\\':
                                state = kEscape3;
                                break;
                                
                            case '[':
                                deep++;
                                value += c;
                                break;
                                
                            case ']':
                                deep--;
                                if (deep < 1) {
                                    metadata[rmWhiteSpaces(key)] = rmWhiteSpaces(value);
                                    state = kLabel;
                                    key = "";
                                    value = "";
                                } else {
                                    value += c;
                                }
                                break;
                            default : value += c;
                        }
                        break;
                        
                    default:
                        std::cerr << "ERROR unrecognized state " << state << std::endl;
                }
            }
            label = rmWhiteSpaces(label);
        }
        
        /**
         * Analyses the widget zone metadata declarations and takes appropriate actions
         */
        void declare(FAUSTFLOAT* zone, const char* key, const char* value)
        {
            if (zone == 0) {
                // special zone 0 means group metadata
                if (strcmp(key, "tooltip") == 0) {
                    // only group tooltip are currently implemented
                    fGroupTooltip = formatTooltip(30, value);
                } else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
            } else {
                if (strcmp(key, "size") == 0) {
                    fGuiSize[zone] = atof(value);
                }
                else if (strcmp(key, "tooltip") == 0) {
                    fTooltip[zone] = formatTooltip(30, value);
                }
                else if (strcmp(key, "unit") == 0) {
                    fUnit[zone] = value;
                }
                else if (strcmp(key, "hidden") == 0) {
                    fHiddenSet.insert(zone);
                }
                else if (strcmp(key, "scale") == 0) {
                    if (strcmp(value, "log") == 0) {
                        fLogSet.insert(zone);
                    } else if (strcmp(value, "exp") == 0) {
                        fExpSet.insert(zone);
                    }
                }
                else if (strcmp(key, "style") == 0) {
                    if (strcmp(value, "knob") == 0) {
                        fKnobSet.insert(zone);
                    } else if (strcmp(value, "led") == 0) {
                        fLedSet.insert(zone);
                    } else if (strcmp(value, "numerical") == 0) {
                        fNumSet.insert(zone);
                    } else {
                        const char* p = value;
                        if (parseWord(p, "radio")) {
                            fRadioDescription[zone] = std::string(p);
                        } else if (parseWord(p, "menu")) {
                            fMenuDescription[zone] = std::string(p);
                        }
                    }
                }
            }
        }
    
};

#endif
/**************************  END  MetaDataUI.h **************************/
/************************** BEGIN ring-buffer.h **************************/
/*
  Copyright (C) 2000 Paul Davis
  Copyright (C) 2003 Rohan Drape
  Copyright (C) 2016 GRAME (renaming for internal use)

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU Lesser General Public License as published by
  the Free Software Foundation; either version 2.1 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.

  ISO/POSIX C version of Paul Davis's lock free ringbuffer C++ code.
  This is safe for the case of one read thread and one write thread.
*/

#ifndef __ring_buffer__
#define __ring_buffer__

#include <stdlib.h>
#include <string.h>

#ifdef WIN32
# pragma warning (disable: 4334)
#else
# pragma GCC diagnostic ignored "-Wunused-function"
#endif

typedef struct {
    char *buf;
    size_t len;
}
ringbuffer_data_t;

typedef struct {
    char *buf;
    volatile size_t write_ptr;
    volatile size_t read_ptr;
    size_t	size;
    size_t	size_mask;
    int	mlocked;
}
ringbuffer_t;

static ringbuffer_t *ringbuffer_create(size_t sz);
static void ringbuffer_free(ringbuffer_t *rb);
static void ringbuffer_get_read_vector(const ringbuffer_t *rb,
                                         ringbuffer_data_t *vec);
static void ringbuffer_get_write_vector(const ringbuffer_t *rb,
                                          ringbuffer_data_t *vec);
static size_t ringbuffer_read(ringbuffer_t *rb, char *dest, size_t cnt);
static size_t ringbuffer_peek(ringbuffer_t *rb, char *dest, size_t cnt);
static void ringbuffer_read_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_read_space(const ringbuffer_t *rb);
static int ringbuffer_mlock(ringbuffer_t *rb);
static void ringbuffer_reset(ringbuffer_t *rb);
static void ringbuffer_reset_size (ringbuffer_t * rb, size_t sz);
static size_t ringbuffer_write(ringbuffer_t *rb, const char *src,
                                 size_t cnt);
static void ringbuffer_write_advance(ringbuffer_t *rb, size_t cnt);
static size_t ringbuffer_write_space(const ringbuffer_t *rb);

/* Create a new ringbuffer to hold at least `sz' bytes of data. The
   actual buffer size is rounded up to the next power of two. */

static ringbuffer_t *
ringbuffer_create (size_t sz)
{
	size_t power_of_two;
	ringbuffer_t *rb;

	if ((rb = (ringbuffer_t *) malloc (sizeof (ringbuffer_t))) == NULL) {
		return NULL;
	}

	for (power_of_two = 1u; 1u << power_of_two < sz; power_of_two++);

	rb->size = 1u << power_of_two;
	rb->size_mask = rb->size;
	rb->size_mask -= 1;
	rb->write_ptr = 0;
	rb->read_ptr = 0;
	if ((rb->buf = (char *) malloc (rb->size)) == NULL) {
		free (rb);
		return NULL;
	}
	rb->mlocked = 0;

	return rb;
}

/* Free all data associated with the ringbuffer `rb'. */

static void
ringbuffer_free (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (rb->mlocked) {
		munlock (rb->buf, rb->size);
	}
#endif /* USE_MLOCK */
	free (rb->buf);
	free (rb);
}

/* Lock the data block of `rb' using the system call 'mlock'.  */

static int
ringbuffer_mlock (ringbuffer_t * rb)
{
#ifdef USE_MLOCK
	if (mlock (rb->buf, rb->size)) {
		return -1;
	}
#endif /* USE_MLOCK */
	rb->mlocked = 1;
	return 0;
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset (ringbuffer_t * rb)
{
	rb->read_ptr = 0;
	rb->write_ptr = 0;
    memset(rb->buf, 0, rb->size);
}

/* Reset the read and write pointers to zero. This is not thread
   safe. */

static void
ringbuffer_reset_size (ringbuffer_t * rb, size_t sz)
{
    rb->size = sz;
    rb->size_mask = rb->size;
    rb->size_mask -= 1;
    rb->read_ptr = 0;
    rb->write_ptr = 0;
}

/* Return the number of bytes available for reading. This is the
   number of bytes in front of the read pointer and behind the write
   pointer.  */

static size_t
ringbuffer_read_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return w - r;
	} else {
		return (w - r + rb->size) & rb->size_mask;
	}
}

/* Return the number of bytes available for writing. This is the
   number of bytes in front of the write pointer and behind the read
   pointer.  */

static size_t
ringbuffer_write_space (const ringbuffer_t * rb)
{
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		return ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		return (r - w) - 1;
	} else {
		return rb->size - 1;
	}
}

/* The copying data reader. Copy at most `cnt' bytes from `rb' to
   `dest'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_read (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[rb->read_ptr]), n1);
	rb->read_ptr = (rb->read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[rb->read_ptr]), n2);
		rb->read_ptr = (rb->read_ptr + n2) & rb->size_mask;
	}

	return to_read;
}

/* The copying data reader w/o read pointer advance. Copy at most
   `cnt' bytes from `rb' to `dest'.  Returns the actual number of bytes
   copied. */

static size_t
ringbuffer_peek (ringbuffer_t * rb, char *dest, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_read;
	size_t n1, n2;
	size_t tmp_read_ptr;

	tmp_read_ptr = rb->read_ptr;

	if ((free_cnt = ringbuffer_read_space (rb)) == 0) {
		return 0;
	}

	to_read = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = tmp_read_ptr + to_read;

	if (cnt2 > rb->size) {
		n1 = rb->size - tmp_read_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_read;
		n2 = 0;
	}

	memcpy (dest, &(rb->buf[tmp_read_ptr]), n1);
	tmp_read_ptr = (tmp_read_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (dest + n1, &(rb->buf[tmp_read_ptr]), n2);
	}

	return to_read;
}

/* The copying data writer. Copy at most `cnt' bytes to `rb' from
   `src'.  Returns the actual number of bytes copied. */

static size_t
ringbuffer_write (ringbuffer_t * rb, const char *src, size_t cnt)
{
	size_t free_cnt;
	size_t cnt2;
	size_t to_write;
	size_t n1, n2;

	if ((free_cnt = ringbuffer_write_space (rb)) == 0) {
		return 0;
	}

	to_write = cnt > free_cnt ? free_cnt : cnt;

	cnt2 = rb->write_ptr + to_write;

	if (cnt2 > rb->size) {
		n1 = rb->size - rb->write_ptr;
		n2 = cnt2 & rb->size_mask;
	} else {
		n1 = to_write;
		n2 = 0;
	}

	memcpy (&(rb->buf[rb->write_ptr]), src, n1);
	rb->write_ptr = (rb->write_ptr + n1) & rb->size_mask;

	if (n2) {
		memcpy (&(rb->buf[rb->write_ptr]), src + n1, n2);
		rb->write_ptr = (rb->write_ptr + n2) & rb->size_mask;
	}

	return to_write;
}

/* Advance the read pointer `cnt' places. */

static void
ringbuffer_read_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->read_ptr + cnt) & rb->size_mask;
	rb->read_ptr = tmp;
}

/* Advance the write pointer `cnt' places. */

static void
ringbuffer_write_advance (ringbuffer_t * rb, size_t cnt)
{
	size_t tmp = (rb->write_ptr + cnt) & rb->size_mask;
	rb->write_ptr = tmp;
}

/* The non-copying data reader. `vec' is an array of two places. Set
   the values at `vec' to hold the current readable data at `rb'. If
   the readable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_read_vector (const ringbuffer_t * rb,
				 ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = w - r;
	} else {
		free_cnt = (w - r + rb->size) & rb->size_mask;
	}

	cnt2 = r + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = rb->size - r;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;

	} else {

		/* Single part vector: just the rest of the buffer */

		vec[0].buf = &(rb->buf[r]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

/* The non-copying data writer. `vec' is an array of two places. Set
   the values at `vec' to hold the current writeable data at `rb'. If
   the writeable data is in one segment the second segment has zero
   length. */

static void
ringbuffer_get_write_vector (const ringbuffer_t * rb,
				  ringbuffer_data_t * vec)
{
	size_t free_cnt;
	size_t cnt2;
	size_t w, r;

	w = rb->write_ptr;
	r = rb->read_ptr;

	if (w > r) {
		free_cnt = ((r - w + rb->size) & rb->size_mask) - 1;
	} else if (w < r) {
		free_cnt = (r - w) - 1;
	} else {
		free_cnt = rb->size - 1;
	}

	cnt2 = w + free_cnt;

	if (cnt2 > rb->size) {

		/* Two part vector: the rest of the buffer after the current write
		   ptr, plus some from the start of the buffer. */

		vec[0].buf = &(rb->buf[w]);
		vec[0].len = rb->size - w;
		vec[1].buf = rb->buf;
		vec[1].len = cnt2 & rb->size_mask;
	} else {
		vec[0].buf = &(rb->buf[w]);
		vec[0].len = free_cnt;
		vec[1].len = 0;
	}
}

#endif // __ring_buffer__
/**************************  END  ring-buffer.h **************************/

/*******************************************************************************
 * GUI : Abstract Graphic User Interface
 * Provides additional mechanisms to synchronize widgets and zones. Widgets
 * should both reflect the value of a zone and allow to change this value.
 ******************************************************************************/

class uiItem;
class GUI;
struct clist;

typedef void (*uiCallback)(FAUSTFLOAT val, void* data);

struct uiItemBase
{
    
    uiItemBase(GUI* ui, FAUSTFLOAT* zone)
    {
        assert(ui);
        assert(zone);
    }
    
    virtual ~uiItemBase()
    {}
    
    virtual void modifyZone(FAUSTFLOAT v) = 0;
    virtual void modifyZone(double date, FAUSTFLOAT v) {}
    virtual double cache() = 0;
    virtual void reflectZone() = 0;
};

// Declared as 'static' to avoid code duplication at link time
static void deleteClist(clist* cl);

struct clist : public std::list<uiItemBase*>
{
    
    virtual ~clist()
    {
        deleteClist(this);
    }
        
};

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data);

typedef std::map<FAUSTFLOAT*, clist*> zmap;

typedef std::map<FAUSTFLOAT*, ringbuffer_t*> ztimedmap;

class GUI : public UI
{
		
    private:
     
        static std::list<GUI*> fGuiList;
        zmap fZoneMap;
        bool fStopped;
        
     public:
            
        GUI():fStopped(false)
        {	
            fGuiList.push_back(this);
        }
        
        virtual ~GUI() 
        {   
            // delete all items
            for (auto& it : fZoneMap) {
                delete it.second;
            }
            // suppress 'this' in static fGuiList
            fGuiList.remove(this);
        }

        // -- registerZone(z,c) : zone management
        
        void registerZone(FAUSTFLOAT* z, uiItemBase* c)
        {
            if (fZoneMap.find(z) == fZoneMap.end()) fZoneMap[z] = new clist();
            fZoneMap[z]->push_back(c);
        }
 
        void updateZone(FAUSTFLOAT* z)
        {
            FAUSTFLOAT v = *z;
            clist* cl = fZoneMap[z];
            for (auto& c : *cl) {
                if (c->cache() != v) c->reflectZone();
            }
        }
    
        void updateAllZones()
        {
            for (auto& m : fZoneMap) {
                updateZone(m.first);
            }
        }
    
        static void updateAllGuis()
        {
            for (auto& g : fGuiList) {
                g->updateAllZones();
            }
        }
    
        static void runAllGuis()
        {
            for (auto& g : fGuiList) {
                g->run();
            }
        }
    
        void addCallback(FAUSTFLOAT* zone, uiCallback foo, void* data)
        {
            createUiCallbackItem(this, zone, foo, data);
        }

        virtual void show() {};	
        virtual bool run() { return false; };

        virtual void stop() { fStopped = true; }
        bool stopped() { return fStopped; }
    
        // -- widget's layouts
        
        virtual void openTabBox(const char* label) {};
        virtual void openHorizontalBox(const char* label) {}
        virtual void openVerticalBox(const char* label) {}
        virtual void closeBox() {}
        
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone) {}
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step) {}
    
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) {}
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) {}
    
        // -- metadata declarations

        virtual void declare(FAUSTFLOAT*, const char*, const char*) {}
    
        // Static global for timed zones, shared between all UI that will set timed values
        static ztimedmap gTimedZoneMap;

};

/**
 * User Interface Item: abstract definition
 */

template <typename REAL>
class uiTypedItem : public uiItemBase
{
    protected:
        
        GUI* fGUI;
        REAL* fZone;
        REAL fCache;
        
        uiTypedItem(GUI* ui, REAL* zone):uiItemBase(ui, static_cast<FAUSTFLOAT*>(zone)),
        fGUI(ui), fZone(zone), fCache(REAL(-123456.654321))
        {
            ui->registerZone(zone, this);
        }
        
    public:
        
        virtual ~uiTypedItem()
        {}
    
        void modifyZone(REAL v)
        {
            fCache = v;
            if (*fZone != v) {
                *fZone = v;
                fGUI->updateZone(fZone);
            }
        }
    
        double cache() { return fCache; }
    
};

class uiItem : public uiTypedItem<FAUSTFLOAT> {
    
    protected:
    
        uiItem(GUI* ui, FAUSTFLOAT* zone):uiTypedItem<FAUSTFLOAT>(ui, zone)
        {}

    public:

        virtual ~uiItem() 
        {}

		void modifyZone(FAUSTFLOAT v)
		{
			fCache = v;
			if (*fZone != v) {
				*fZone = v;
				fGUI->updateZone(fZone);
			}
		}

};

/**
 * Base class for items with a converter
 */

struct uiConverter {
    
    ValueConverter* fConverter;
    
    uiConverter(MetaDataUI::Scale scale, FAUSTFLOAT umin, FAUSTFLOAT umax, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
    {
        // Select appropriate converter according to scale mode
        if (scale == MetaDataUI::kLog) {
            fConverter = new LogValueConverter(umin, umax, fmin, fmax);
        } else if (scale == MetaDataUI::kExp) {
            fConverter = new ExpValueConverter(umin, umax, fmin, fmax);
        } else {
            fConverter = new LinearValueConverter(umin, umax, fmin, fmax);
        }
    }
    
    virtual ~uiConverter()
    {
        delete fConverter;
    }
};

/**
 * User Interface item owned (and so deleted) by external code
 */

class uiOwnedItem : public uiItem {
    
    protected:
    
        uiOwnedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
    
     public:
    
        virtual ~uiOwnedItem()
        {}
    
        virtual void reflectZone() {}
};

/**
 * Callback Item
 */

class uiCallbackItem : public uiItem {
    
    protected:
    
        uiCallback fCallback;
        void* fData;
    
    public:
    
        uiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
        : uiItem(ui, zone), fCallback(foo), fData(data) {}
        
        virtual void reflectZone() 
        {		
            FAUSTFLOAT v = *fZone;
            fCache = v; 
            fCallback(v, fData);	
        }
};

/**
 *  For timestamped control
 */

struct DatedControl {
    
    double fDate;
    FAUSTFLOAT fValue;
    
    DatedControl(double d = 0., FAUSTFLOAT v = FAUSTFLOAT(0)):fDate(d), fValue(v) {}
    
};

/**
 * Base class for timed items
 */

class uiTimedItem : public uiItem
{
    
    protected:
        
        bool fDelete;
        
    public:
    
        using uiItem::modifyZone;
        
        uiTimedItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {
            if (GUI::gTimedZoneMap.find(fZone) == GUI::gTimedZoneMap.end()) {
                GUI::gTimedZoneMap[fZone] = ringbuffer_create(8192);
                fDelete = true;
            } else {
                fDelete = false;
            }
        }
        
        virtual ~uiTimedItem()
        {
            ztimedmap::iterator it;
            if (fDelete && ((it = GUI::gTimedZoneMap.find(fZone)) != GUI::gTimedZoneMap.end())) {
                ringbuffer_free((*it).second);
                GUI::gTimedZoneMap.erase(it);
            }
        }
        
        virtual void modifyZone(double date, FAUSTFLOAT v)
        {
            size_t res;
            DatedControl dated_val(date, v);
            if ((res = ringbuffer_write(GUI::gTimedZoneMap[fZone], (const char*)&dated_val, sizeof(DatedControl))) != sizeof(DatedControl)) {
                std::cerr << "ringbuffer_write error DatedControl" << std::endl;
            }
        }
    
};

/**
 * Allows to group a set of zones
 */

class uiGroupItem : public uiItem
{
    protected:
    
        std::vector<FAUSTFLOAT*> fZoneMap;

    public:
    
        uiGroupItem(GUI* ui, FAUSTFLOAT* zone):uiItem(ui, zone)
        {}
        virtual ~uiGroupItem() 
        {}
        
        virtual void reflectZone() 
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            
            // Update all zones of the same group
            for (auto& it : fZoneMap) {
                *it = v;
            }
        }
        
        void addZone(FAUSTFLOAT* zone) { fZoneMap.push_back(zone); }

};

// Can not be defined as method in the classes

static void createUiCallbackItem(GUI* ui, FAUSTFLOAT* zone, uiCallback foo, void* data)
{
    new uiCallbackItem(ui, zone, foo, data);
}

static void deleteClist(clist* cl)
{
    for (auto& it : *cl) {
        // This specific code is only used in JUCE context. TODO: use proper 'shared_ptr' based memory management.
    #if defined(JUCE_32BIT) || defined(JUCE_64BIT)
        uiOwnedItem* owned = dynamic_cast<uiOwnedItem*>(it);
        // owned items are deleted by external code
        if (!owned) {
            delete it;
        }
    #else
        delete it;
    #endif
    }
}

#endif
/**************************  END  GUI.h **************************/
/************************** BEGIN JSONUI.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/
 
#ifndef FAUST_JSONUI_H
#define FAUST_JSONUI_H

#include <vector>
#include <map>
#include <string>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <algorithm>


/*******************************************************************************
 * JSONUI : Faust User Interface
 * This class produce a complete JSON decription of the DSP instance.
 ******************************************************************************/

template <typename REAL>
class JSONUIReal : public PathBuilder, public Meta, public UIReal<REAL>
{

    protected:
    
        std::stringstream fUI;
        std::stringstream fMeta;
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        std::string fVersion;           // Compiler version
        std::string fCompileOptions;    // Compilation options
        std::vector<std::string> fLibraryList;
        std::vector<std::string> fIncludePathnames;
        std::string fName;
        std::string fFileName;
        std::string fExpandedCode;
        std::string fSHAKey;
        int fDSPSize;                   // In bytes
        std::map<std::string, int> fPathTable;
        bool fExtended;
    
        char fCloseUIPar;
        char fCloseMetaPar;
        int fTab;
    
        int fInputs, fOutputs, fSRIndex;
         
        void tab(int n, std::ostream& fout)
        {
            fout << '\n';
            while (n-- > 0) {
                fout << '\t';
            }
        }
    
        std::string flatten(const std::string& src)
        {
            std::string dst;
            for (size_t i = 0; i < src.size(); i++) {
                switch (src[i]) {
                    case '\n':
                    case '\t':
                        break;
                    default:
                        dst += src[i];
                        break;
                }
            }
            return dst;
        }
    
        void addMeta(int tab_val, bool quote = true)
        {
            if (fMetaAux.size() > 0) {
                tab(tab_val, fUI); fUI << "\"meta\": [";
                std::string sep = "";
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    fUI << sep;
                    tab(tab_val + 1, fUI); fUI << "{ \"" << fMetaAux[i].first << "\": \"" << fMetaAux[i].second << "\" }";
                    sep = ",";
                }
                tab(tab_val, fUI); fUI << ((quote) ? "],": "]");
                fMetaAux.clear();
            }
        }
    
        int getAddressIndex(const std::string& path)
        {
            return (fPathTable.find(path) != fPathTable.end()) ? fPathTable[path] : -1;
        }
      
     public:
     
        JSONUIReal(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const std::map<std::string, int>& path_table)
        {
            init(name, filename, inputs, outputs, sr_index, sha_key, dsp_code, version, compile_options, library_list, include_pathnames, size, path_table);
        }

        JSONUIReal(const std::string& name, const std::string& filename, int inputs, int outputs)
        {
            init(name, filename, inputs, outputs, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }

        JSONUIReal(int inputs, int outputs)
        {
            init("", "", inputs, outputs, -1, "", "","", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
        
        JSONUIReal()
        {
            init("", "", -1, -1, -1, "", "", "", "", std::vector<std::string>(), std::vector<std::string>(), -1, std::map<std::string, int>());
        }
 
        virtual ~JSONUIReal() {}
        
        void setInputs(int inputs) { fInputs = inputs; }
        void setOutputs(int outputs) { fOutputs = outputs; }
    
        void setSRIndex(int sr_index) { fSRIndex = sr_index; }
    
        // Init may be called multiple times so fMeta and fUI are reinitialized
        void init(const std::string& name,
                  const std::string& filename,
                  int inputs,
                  int outputs,
                  int sr_index,
                  const std::string& sha_key,
                  const std::string& dsp_code,
                  const std::string& version,
                  const std::string& compile_options,
                  const std::vector<std::string>& library_list,
                  const std::vector<std::string>& include_pathnames,
                  int size,
                  const std::map<std::string, int>& path_table,
                  bool extended = false)
        {
            fTab = 1;
            fExtended = extended;
            if (fExtended) {
                fUI << std::setprecision(std::numeric_limits<REAL>::max_digits10);
                fMeta << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            
            // Start Meta generation
            fMeta.str("");
            tab(fTab, fMeta); fMeta << "\"meta\": [";
            fCloseMetaPar = ' ';
            
            // Start UI generation
            fUI.str("");
            tab(fTab, fUI); fUI << "\"ui\": [";
            fCloseUIPar = ' ';
            fTab += 1;
            
            fName = name;
            fFileName = filename;
            fInputs = inputs;
            fOutputs = outputs;
            fSRIndex = sr_index;
            fExpandedCode = dsp_code;
            fSHAKey = sha_key;
            fDSPSize = size;
            fPathTable = path_table;
            fVersion = version;
            fCompileOptions = compile_options;
            fLibraryList = library_list;
            fIncludePathnames = include_pathnames;
        }
   
        // -- widget's layouts
    
        virtual void openGenericGroup(const char* label, const char* name)
        {
            pushLabel(label);
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"items\": [";
            fCloseUIPar = ' ';
            fTab += 1;
        }

        virtual void openTabBox(const char* label)
        {
            openGenericGroup(label, "tgroup");
        }
    
        virtual void openHorizontalBox(const char* label)
        {
            openGenericGroup(label, "hgroup");
        }
    
        virtual void openVerticalBox(const char* label)
        {
            openGenericGroup(label, "vgroup");
        }
    
        virtual void closeBox()
        {
            popLabel();
            fTab -= 1;
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        // -- active widgets
  
        virtual void addGenericButton(const char* label, const char* name)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ((fMetaAux.size() > 0) ? "," : "");
            } else {
                tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fMetaAux.size() > 0) ? "," : "");
            }
            addMeta(fTab, false);
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "button");
        }
    
        virtual void addCheckButton(const char* label, REAL* zone)
        {
            addGenericButton(label, "checkbox");
        }

        virtual void addGenericEntry(const char* label, const char* name, REAL init, REAL min, REAL max, REAL step)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"init\": " << init << ",";
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max << ",";
            tab(fTab, fUI); fUI << "\"step\": " << step;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }
    
        virtual void addVerticalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "vslider", init, min, max, step);
        }
    
        virtual void addHorizontalSlider(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "hslider", init, min, max, step);
        }
    
        virtual void addNumEntry(const char* label, REAL* zone, REAL init, REAL min, REAL max, REAL step)
        {
            addGenericEntry(label, "nentry", init, min, max, step);
        }

        // -- passive widgets
    
        virtual void addGenericBargraph(const char* label, const char* name, REAL min, REAL max) 
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << name << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\",";
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path) << ",";
            }
            addMeta(fTab);
            tab(fTab, fUI); fUI << "\"min\": " << min << ",";
            tab(fTab, fUI); fUI << "\"max\": " << max;
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        virtual void addHorizontalBargraph(const char* label, REAL* zone, REAL min, REAL max) 
        {
            addGenericBargraph(label, "hbargraph", min, max);
        }
    
        virtual void addVerticalBargraph(const char* label, REAL* zone, REAL min, REAL max)
        {
            addGenericBargraph(label, "vbargraph", min, max);
        }
    
        virtual void addSoundfile(const char* label, const char* url, Soundfile** zone)
        {
            std::string path = buildPath(label);
            
            fUI << fCloseUIPar;
            tab(fTab, fUI); fUI << "{";
            fTab += 1;
            tab(fTab, fUI); fUI << "\"type\": \"" << "soundfile" << "\",";
            tab(fTab, fUI); fUI << "\"label\": \"" << label << "\"" << ",";
            tab(fTab, fUI); fUI << "\"url\": \"" << url << "\"" << ",";
            tab(fTab, fUI); fUI << "\"address\": \"" << path << "\"" << ((fPathTable.size() > 0) ? "," : "");
            if (fPathTable.size() > 0) {
                tab(fTab, fUI); fUI << "\"index\": " << getAddressIndex(path);
            }
            fTab -= 1;
            tab(fTab, fUI); fUI << "}";
            fCloseUIPar = ',';
        }

        // -- metadata declarations

        virtual void declare(REAL* zone, const char* key, const char* val)
        {
            fMetaAux.push_back(std::make_pair(key, val));
        }
    
        // Meta interface
        virtual void declare(const char* key, const char* value)
        {
            fMeta << fCloseMetaPar;
            // fName found in metadata
            if ((strcmp(key, "name") == 0) && (fName == "")) fName = value;
            // fFileName found in metadata
            if ((strcmp(key, "filename") == 0) && (fFileName == "")) fFileName = value;
            tab(fTab, fMeta); fMeta << "{ " << "\"" << key << "\"" << ": " << "\"" << value << "\" }";
            fCloseMetaPar = ',';
        }
    
        std::string JSON(bool flat = false)
        {
            fTab = 0;
            std::stringstream JSON;
            if (fExtended) {
                JSON << std::setprecision(std::numeric_limits<REAL>::max_digits10);
            }
            JSON << "{";
            fTab += 1;
            tab(fTab, JSON); JSON << "\"name\": \"" << fName << "\",";
            tab(fTab, JSON); JSON << "\"filename\": \"" << fFileName << "\",";
            if (fVersion != "") { tab(fTab, JSON); JSON << "\"version\": \"" << fVersion << "\","; }
            if (fCompileOptions != "") { tab(fTab, JSON); JSON << "\"compile_options\": \"" <<  fCompileOptions << "\","; }
            if (fLibraryList.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"library_list\": [";
                for (size_t i = 0; i < fLibraryList.size(); i++) {
                    JSON << "\"" << fLibraryList[i] << "\"";
                    if (i < (fLibraryList.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fIncludePathnames.size() > 0) {
                tab(fTab, JSON);
                JSON << "\"include_pathnames\": [";
                for (size_t i = 0; i < fIncludePathnames.size(); i++) {
                    JSON << "\"" << fIncludePathnames[i] << "\"";
                    if (i < (fIncludePathnames.size() - 1)) JSON << ",";
                }
                JSON << "],";
            }
            if (fDSPSize != -1) { tab(fTab, JSON); JSON << "\"size\": " << fDSPSize << ","; }
            if (fSHAKey != "") { tab(fTab, JSON); JSON << "\"sha_key\": \"" << fSHAKey << "\","; }
            if (fExpandedCode != "") { tab(fTab, JSON); JSON << "\"code\": \"" << fExpandedCode << "\","; }
            tab(fTab, JSON); JSON << "\"inputs\": " << fInputs << ",";
            tab(fTab, JSON); JSON << "\"outputs\": " << fOutputs << ",";
            if (fSRIndex != -1) { tab(fTab, JSON); JSON << "\"sr_index\": " << fSRIndex << ","; }
            tab(fTab, fMeta); fMeta << "],";
            tab(fTab, fUI); fUI << "]";
            fTab -= 1;
            if (fCloseMetaPar == ',') { // If "declare" has been called, fCloseMetaPar state is now ','
                JSON << fMeta.str() << fUI.str();
            } else {
                JSON << fUI.str();
            }
            tab(fTab, JSON); JSON << "}";
            return (flat) ? flatten(JSON.str()) : JSON.str();
        }
    
};

// Externally available class using FAUSTFLOAT

struct JSONUI : public JSONUIReal<FAUSTFLOAT>, public UI
{
    
    JSONUI(const std::string& name,
           const std::string& filename,
           int inputs,
           int outputs,
           int sr_index,
           const std::string& sha_key,
           const std::string& dsp_code,
           const std::string& version,
           const std::string& compile_options,
           const std::vector<std::string>& library_list,
           const std::vector<std::string>& include_pathnames,
           int size,
           const std::map<std::string, int>& path_table):
    JSONUIReal<FAUSTFLOAT>(name, filename,
                          inputs, outputs,
                          sr_index,
                          sha_key, dsp_code,
                          version, compile_options,
                          library_list, include_pathnames,
                          size, path_table)
    {}
    
    JSONUI(const std::string& name, const std::string& filename, int inputs, int outputs):
    JSONUIReal<FAUSTFLOAT>(name, filename, inputs, outputs)
    {}
    
    JSONUI(int inputs, int outputs):JSONUIReal<FAUSTFLOAT>(inputs, outputs)
    {}
    
    JSONUI():JSONUIReal<FAUSTFLOAT>()
    {}

    virtual void openTabBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openTabBox(label);
    }
    virtual void openHorizontalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openHorizontalBox(label);
    }
    virtual void openVerticalBox(const char* label)
    {
        JSONUIReal<FAUSTFLOAT>::openVerticalBox(label);
    }
    virtual void closeBox()
    {
        JSONUIReal<FAUSTFLOAT>::closeBox();
    }
    
    // -- active widgets
    
    virtual void addButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addButton(label, zone);
    }
    virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
    {
        JSONUIReal<FAUSTFLOAT>::addCheckButton(label, zone);
    }
    virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalSlider(label, zone, init, min, max, step);
    }
    virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalSlider(label, zone, init, min, max, step);
    }
    virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
    {
        JSONUIReal<FAUSTFLOAT>::addNumEntry(label, zone, init, min, max, step);
    }
    
    // -- passive widgets
    
    virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addHorizontalBargraph(label, zone, min, max);
    }
    virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
    {
        JSONUIReal<FAUSTFLOAT>::addVerticalBargraph(label, zone, min, max);
    }
    
    // -- soundfiles
    
    virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone)
    {
        JSONUIReal<FAUSTFLOAT>::addSoundfile(label, filename, sf_zone);
    }
    
    // -- metadata declarations
    
    virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(zone, key, val);
    }

    virtual void declare(const char* key, const char* val)
    {
        JSONUIReal<FAUSTFLOAT>::declare(key, val);
    }

    virtual ~JSONUI() {}
    
};

#endif // FAUST_JSONUI_H
/**************************  END  JSONUI.h **************************/
/************************** BEGIN midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __midi__
#define __midi__

#include <vector>
#include <string>
#include <algorithm>
#include <assert.h>

class MapUI;

/*************************************
 A time-stamped short MIDI message
**************************************/

// Force contiguous memory layout
#pragma pack (push, 1)
struct MIDIMessage
{
    uint32_t frameIndex;
    uint8_t byte0, byte1, byte2;
};
#pragma pack (pop)

/*******************************************************************************
 * MIDI processor definition.
 *
 * MIDI input or output handling classes will implement this interface,
 * so the same method names (keyOn, ctrlChange...) will be used either
 * when decoding MIDI input or encoding MIDI output events.
 *******************************************************************************/

class midi {

    public:

        midi() {}
        virtual ~midi() {}

        // Additional time-stamped API for MIDI input
        virtual MapUI* keyOn(double, int channel, int pitch, int velocity)
        {
            return keyOn(channel, pitch, velocity);
        }
        
        virtual void keyOff(double, int channel, int pitch, int velocity = 127)
        {
            keyOff(channel, pitch, velocity);
        }
    
        virtual void keyPress(double, int channel, int pitch, int press)
        {
            keyPress(channel, pitch, press);
        }
        
        virtual void chanPress(double date, int channel, int press)
        {
            chanPress(channel, press);
        }
    
        virtual void pitchWheel(double, int channel, int wheel)
        {
            pitchWheel(channel, wheel);
        }
           
        virtual void ctrlChange(double, int channel, int ctrl, int value)
        {
            ctrlChange(channel, ctrl, value);
        }
    
        virtual void ctrlChange14bits(double, int channel, int ctrl, int value)
        {
            ctrlChange14bits(channel, ctrl, value);
        }
    
        virtual void rpn(double, int channel, int ctrl, int value)
        {
            rpn(channel, ctrl, value);
        }

        virtual void progChange(double, int channel, int pgm)
        {
            progChange(channel, pgm);
        }
    
        virtual void sysEx(double, std::vector<unsigned char>& message)
        {
            sysEx(message);
        }

        // MIDI sync
        virtual void startSync(double date)  {}
        virtual void stopSync(double date)   {}
        virtual void clock(double date)  {}

        // Standard MIDI API
        virtual MapUI* keyOn(int channel, int pitch, int velocity)      { return nullptr; }
        virtual void keyOff(int channel, int pitch, int velocity)       {}
        virtual void keyPress(int channel, int pitch, int press)        {}
        virtual void chanPress(int channel, int press)                  {}
        virtual void ctrlChange(int channel, int ctrl, int value)       {}
        virtual void ctrlChange14bits(int channel, int ctrl, int value) {}
        virtual void rpn(int channel, int ctrl, int value)              {}
        virtual void pitchWheel(int channel, int wheel)                 {}
        virtual void progChange(int channel, int pgm)                   {}
        virtual void sysEx(std::vector<unsigned char>& message)         {}

        enum MidiStatus {
            // channel voice messages
            MIDI_NOTE_OFF = 0x80,
            MIDI_NOTE_ON = 0x90,
            MIDI_CONTROL_CHANGE = 0xB0,
            MIDI_PROGRAM_CHANGE = 0xC0,
            MIDI_PITCH_BEND = 0xE0,
            MIDI_AFTERTOUCH = 0xD0,         // aka channel pressure
            MIDI_POLY_AFTERTOUCH = 0xA0,    // aka key pressure
            MIDI_CLOCK = 0xF8,
            MIDI_START = 0xFA,
            MIDI_CONT = 0xFB,
            MIDI_STOP = 0xFC,
            MIDI_SYSEX_START = 0xF0,
            MIDI_SYSEX_STOP = 0xF7
        };

        enum MidiCtrl {
            ALL_NOTES_OFF = 123,
            ALL_SOUND_OFF = 120
        };
    
        enum MidiNPN {
            PITCH_BEND_RANGE = 0
        };

};

/*
 A class to decode NRPN and RPN messages, adapted from JUCE forum message: https://forum.juce.com/t/14bit-midi-controller-support/11517
*/

class MidiNRPN {
    
    private:
    
        bool ctrlnew;
        int ctrlnum;
        int ctrlval;
        
        int nrpn_lsb, nrpn_msb;
        int data_lsb, data_msb;
        
        enum
        {
            midi_nrpn_lsb = 98,
            midi_nrpn_msb = 99,
            midi_rpn_lsb  = 100,
            midi_rpn_msb  = 101,
            midi_data_lsb = 38,
            midi_data_msb = 6
        };
    
    public:
        
        MidiNRPN(): ctrlnew(false), nrpn_lsb(-1), nrpn_msb(-1), data_lsb(-1), data_msb(-1)
        {}
        
        // return true if the message has been filtered
        bool process(int data1, int data2)
        {
            switch (data1)
            {
                case midi_nrpn_lsb: nrpn_lsb = data2; return true;
                case midi_nrpn_msb: nrpn_msb = data2; return true;
                case midi_rpn_lsb: {
                    if (data2 == 127) {
                        nrpn_lsb = data_lsb = -1;
                    } else {
                        nrpn_lsb = 0;
                        data_lsb = -1;
                    }
                    return true;
                }
                case midi_rpn_msb: {
                    if (data2 == 127) {
                        nrpn_msb = data_msb = -1;
                    } else {
                        nrpn_msb = 0;
                        data_msb = -1;
                    }
                    return true;
                }
                case midi_data_lsb:
                case midi_data_msb:
                {
                    if (data1 == midi_data_msb) {
                        if (nrpn_msb < 0) {
                            return false;
                        }
                        data_msb = data2;
                    } else { // midi_data_lsb
                        if (nrpn_lsb < 0) {
                            return false;
                        }
                        data_lsb = data2;
                    }
                    if (data_lsb >= 0 && data_msb >= 0) {
                        ctrlnum = (nrpn_msb << 7) | nrpn_lsb;
                        ctrlval = (data_msb << 7) | data_lsb;
                        data_lsb = data_msb = -1;
                        nrpn_msb = nrpn_lsb = -1;
                        ctrlnew = true;
                    }
                    return true;
                }
                default: return false;
            };
        }
        
        bool hasNewNRPN() { bool res = ctrlnew; ctrlnew = false; return res; }
        
        // results in [0, 16383]
        int getCtrl() const { return ctrlnum; }
        int getVal() const { return ctrlval; }
    
};


/****************************************************
 * Base class for MIDI input handling.
 *
 * Shared common code used for input handling:
 * - decoding Real-Time messages: handleSync
 * - decoding one data byte messages: handleData1
 * - decoding two data byte messages: handleData2
 * - getting ready messages in polling mode
 ****************************************************/

class midi_handler : public midi {

    protected:

        std::vector<midi*> fMidiInputs;
        std::string fName;
        MidiNRPN fNRPN;
    
        int range(int min, int max, int val) { return (val < min) ? min : ((val >= max) ? max : val); }
  
    public:

        midi_handler(const std::string& name = "MIDIHandler"):fName(name) {}
        virtual ~midi_handler() {}

        void addMidiIn(midi* midi_dsp) { if (midi_dsp) fMidiInputs.push_back(midi_dsp); }
        void removeMidiIn(midi* midi_dsp)
        {
            std::vector<midi*>::iterator it = std::find(fMidiInputs.begin(), fMidiInputs.end(), midi_dsp);
            if (it != fMidiInputs.end()) {
                fMidiInputs.erase(it);
            }
        }

        // Those 2 methods have to be implemented by subclasses
        virtual bool startMidi() { return true; }
        virtual void stopMidi() {}
    
        void setName(const std::string& name) { fName = name; }
        std::string getName() { return fName; }
    
        // To be used in polling mode
        virtual int recvMessages(std::vector<MIDIMessage>* message) { return 0; }
        virtual void sendMessages(std::vector<MIDIMessage>* message, int count) {}
    
        // MIDI Real-Time
        void handleClock(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->clock(time);
            }
        }
        
        void handleStart(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->startSync(time);
            }
        }
        
        void handleStop(double time)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->stopSync(time);
            }
        }
    
        void handleSync(double time, int type)
        {
            if (type == MIDI_CLOCK) {
                handleClock(time);
            // We can consider start and continue as identical messages
            } else if ((type == MIDI_START) || (type == MIDI_CONT)) {
                handleStart(time);
            } else if (type == MIDI_STOP) {
                handleStop(time);
            }
        }
    
        // MIDI 1 data
        void handleProgChange(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->progChange(time, channel, data1);
            }
        }
    
        void handleAfterTouch(double time, int channel, int data1)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->chanPress(time, channel, data1);
            }
        }

        void handleData1(double time, int type, int channel, int data1)
        {
            if (type == MIDI_PROGRAM_CHANGE) {
                handleProgChange(time, channel, data1);
            } else if (type == MIDI_AFTERTOUCH) {
                handleAfterTouch(time, channel, data1);
            }
        }
    
        // MIDI 2 datas
        void handleKeyOff(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyOff(time, channel, data1, data2);
            }
        }
        
        void handleKeyOn(double time, int channel, int data1, int data2)
        {
            if (data2 == 0) {
                handleKeyOff(time, channel, data1, data2);
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->keyOn(time, channel, data1, data2);
                }
            }
        }
    
        void handleCtrlChange(double time, int channel, int data1, int data2)
        {
            // Special processing for NRPN and RPN
            if (fNRPN.process(data1, data2)) {
                if (fNRPN.hasNewNRPN()) {
                    for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                        fMidiInputs[i]->rpn(time, channel, fNRPN.getCtrl(), fNRPN.getVal());
                    }
                }
            } else {
                for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                    fMidiInputs[i]->ctrlChange(time, channel, data1, data2);
                }
            }
        }
        
        void handlePitchWheel(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, (data2 << 7) + data1);
            }
        }
    
        void handlePitchWheel(double time, int channel, int bend)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->pitchWheel(time, channel, bend);
            }
        }
        
        void handlePolyAfterTouch(double time, int channel, int data1, int data2)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->keyPress(time, channel, data1, data2);
            }
        }
  
        void handleData2(double time, int type, int channel, int data1, int data2)
        {
            if (type == MIDI_NOTE_OFF) {
                handleKeyOff(time, channel,  data1, data2);
            } else if (type == MIDI_NOTE_ON) {
                handleKeyOn(time, channel, data1, data2);
            } else if (type == MIDI_CONTROL_CHANGE) {
                handleCtrlChange(time, channel, data1, data2);
            } else if (type == MIDI_PITCH_BEND) {
                handlePitchWheel(time, channel, data1, data2);
            } else if (type == MIDI_POLY_AFTERTOUCH) {
                handlePolyAfterTouch(time, channel, data1, data2);
            }
        }
    
        // SysEx
        void handleSysex(double time, std::vector<unsigned char>& message)
        {
            for (unsigned int i = 0; i < fMidiInputs.size(); i++) {
                fMidiInputs[i]->sysEx(time, message);
            }
        }
    
        void handleMessage(double time, int type, std::vector<unsigned char>& message)
        {
            if (type == MIDI_SYSEX_START) {
                handleSysex(time, message);
            }
        }
  
};

//-------------------------------
// For timestamped MIDI messages
//-------------------------------

struct DatedMessage {
    
    double fDate;
    unsigned char fBuffer[3];
    size_t fSize;
    
    DatedMessage(double date, unsigned char* buffer, size_t size)
    :fDate(date), fSize(size)
    {
        assert(size <= 3);
        memcpy(fBuffer, buffer, size);
    }
    
    DatedMessage():fDate(0.0), fSize(0)
    {}
    
};

#endif // __midi__
/**************************  END  midi.h **************************/

#ifdef _MSC_VER
#define gsscanf sscanf_s
#else
#define gsscanf sscanf
#endif

/*****************************************************************************
* Helper code for MIDI meta and polyphonic 'nvoices' parsing
******************************************************************************/

struct MidiMeta : public Meta, public std::map<std::string, std::string> {
    
    void declare(const char* key, const char* value)
    {
        (*this)[key] = value;
    }
    
    const std::string get(const char* key, const char* def)
    {
        return (this->find(key) != this->end()) ? (*this)[key] : def;
    }
    
    static void analyse(dsp* mono_dsp, bool& midi_sync, int& nvoices)
    {
        JSONUI jsonui;
        mono_dsp->buildUserInterface(&jsonui);
        std::string json = jsonui.JSON();
        midi_sync = ((json.find("midi") != std::string::npos) &&
                     ((json.find("start") != std::string::npos) ||
                      (json.find("stop") != std::string::npos) ||
                      (json.find("clock") != std::string::npos) ||
                      (json.find("timestamp") != std::string::npos)));
    
    #if defined(NVOICES) && NVOICES!=NUM_VOICES
        nvoices = NVOICES;
    #else
        MidiMeta meta;
        mono_dsp->metadata(&meta);
        bool found_voices = false;
        // If "options" metadata is used
        std::string options = meta.get("options", "");
        if (options != "") {
            std::map<std::string, std::string> metadata;
            std::string res;
            MetaDataUI::extractMetadata(options, res, metadata);
            if (metadata.find("nvoices") != metadata.end()) {
                nvoices = std::atoi(metadata["nvoices"].c_str());
                found_voices = true;
            }
        }
        // Otherwise test for "nvoices" metadata
        if (!found_voices) {
            std::string numVoices = meta.get("nvoices", "0");
            nvoices = std::atoi(numVoices.c_str());
        }
        nvoices = std::max<int>(0, nvoices);
    #endif
    }
    
    static bool checkPolyphony(dsp* mono_dsp)
    {
        MapUI map_ui;
        mono_dsp->buildUserInterface(&map_ui);
        bool has_freq = false;
        bool has_gate = false;
        bool has_gain = false;
        for (int i = 0; i < map_ui.getParamsCount(); i++) {
            std::string path = map_ui.getParamAddress(i);
            has_freq |= MapUI::endsWith(path, "/freq");
            has_gate |= MapUI::endsWith(path, "/gate");
            has_gain |= MapUI::endsWith(path, "/gain");
        }
        return (has_freq && has_gate && has_gain);
    }
    
};

/*******************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI meta data and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data is handled.
 ******************************************************************************/

class uiMidi {
    
    friend class MidiUI;
    
    protected:
        
        midi* fMidiOut;
        bool fInputCtrl;
        int fChan;
    
        // To be used when sending messages, returns the effective chan, or 0 when fChan is initialized with -1 (means 'all chans')
        int rangeChan() { return (((fChan < 0) || (fChan > 15)) ? 0 : fChan); }
        bool inRange(FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT v) { return (min <= v && v <= max); }
    
    public:
        
        uiMidi(midi* midi_out, bool input, int chan = -1):fMidiOut(midi_out), fInputCtrl(input), fChan(chan)
        {}
        virtual ~uiMidi()
        {}

};

/*****************************************************************************
 * Base class for MIDI aware UI items
 ******************************************************************************/

class uiMidiItem : public uiMidi, public uiItem {
    
    public:
        
        uiMidiItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidi(midi_out, input, chan), uiItem(ui, zone)
        {}
        virtual ~uiMidiItem()
        {}
    
        virtual void reflectZone() {}
    
};

/*****************************************************************************
 * Base class for MIDI aware UI items with timestamp support
 ******************************************************************************/

class uiMidiTimedItem : public uiMidi, public uiTimedItem {
    
    public:
        
        uiMidiTimedItem(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true, int chan = -1)
            :uiMidi(midi_out, input, chan), uiTimedItem(ui, zone)
        {}
        virtual ~uiMidiTimedItem()
        {}
    
        virtual void reflectZone() {}
    
};

//-----------
// MIDI sync
//-----------

class uiMidiStart : public uiMidiTimedItem
{
  
    public:
    
        uiMidiStart(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStart()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(0)) {
                fMidiOut->startSync(0);
            }
        }
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
        
};

class uiMidiStop : public uiMidiTimedItem {
  
    public:
    
        uiMidiStop(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input)
        {}
        virtual ~uiMidiStop()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (v != FAUSTFLOAT(1)) {
                fMidiOut->stopSync(0);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(v));
            }
        }
};

class uiMidiClock : public uiMidiTimedItem {

    private:
        
        bool fState;
  
    public:
    
        uiMidiClock(midi* midi_out, GUI* ui, FAUSTFLOAT* zone, bool input = true)
            :uiMidiTimedItem(midi_out, ui, zone, input), fState(false)
        {}
        virtual ~uiMidiClock()
        {}
    
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->clock(0);
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                fState = !fState;
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fState));
            }
        }

};

//----------------------
// Standard MIDI events
//----------------------

//---------------------------------------------
// uiMidiProgChange uses the [min...max] range
//---------------------------------------------

class uiMidiProgChange : public uiMidiTimedItem {
    
    public:
    
        FAUSTFLOAT fMin, fMax;
    
        uiMidiProgChange(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), fMin(min), fMax(max)
        {}
        virtual ~uiMidiProgChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            if (inRange(fMin, fMax, v)) {
                fMidiOut->progChange(rangeChan(), v);
            }
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiItem::modifyZone(v);
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl && inRange(fMin, fMax, v)) {
                uiMidiTimedItem::modifyZone(date, v);
            }
        }
        
};

class uiMidiChanPress : public uiMidiTimedItem, public uiConverter {
    
    private:
        
        int fPress;
  
    public:
    
        uiMidiChanPress(midi* midi_out, GUI* ui,
                        FAUSTFLOAT* zone,
                        FAUSTFLOAT min, FAUSTFLOAT max,
                        bool input = true,
                        MetaDataUI::Scale scale = MetaDataUI::kLin,
                        int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max)
        {}
        virtual ~uiMidiChanPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->chanPress(rangeChan(), fConverter->faust2ui(v));
        }
    
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
        
};

//------------------------------------------------------
// uiMidiCtrlChange does scale (kLin/kLog/kExp) mapping
//------------------------------------------------------

class uiMidiCtrlChange : public uiMidiTimedItem, public uiConverter {
    
    private:
    
        int fCtrl;
 
    public:

        uiMidiCtrlChange(midi* midi_out, int ctrl, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fCtrl(ctrl)
        {}
        virtual ~uiMidiCtrlChange()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->ctrlChange(rangeChan(), fCtrl, fConverter->faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
};

class uiMidiPitchWheel : public uiMidiTimedItem {

    private:
    
        LinearValueConverter2 fConverter;
    
    public:
    
        uiMidiPitchWheel(midi* midi_out, GUI* ui, FAUSTFLOAT* zone,
                         FAUSTFLOAT min, FAUSTFLOAT max,
                         bool input = true, int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan)
        {
            if (min <= 0 && max >= 0) {
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min), 0., double(max));
            } else {
                // Degenerated case...
                fConverter = LinearValueConverter2(0., 8191., 16383., double(min),double(min + (max - min)/FAUSTFLOAT(2)), double(max));
            }
        }
    
        virtual ~uiMidiPitchWheel()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->pitchWheel(rangeChan(), fConverter.faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(FAUSTFLOAT(fConverter.ui2faust(v)));
            }
        }
    
        void setRange(int val)
        {
            double semi = (val / 128) + ((val % 128) / 100.);
            fConverter.setMappingValues(0., 8191., 16383., -semi, 0., semi);
        }
 
};

//--------------------------------------------------------------
// uiMidiKeyOn does scale (kLin/kLog/kExp) mapping for velocity
//--------------------------------------------------------------

class uiMidiKeyOn : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOn;
  
    public:
    
        uiMidiKeyOn(midi* midi_out, int key, GUI* ui,
                    FAUSTFLOAT* zone,
                    FAUSTFLOAT min, FAUSTFLOAT max,
                    bool input = true,
                    MetaDataUI::Scale scale = MetaDataUI::kLin,
                    int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOn(key)
        {}
        virtual ~uiMidiKeyOn()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOn(rangeChan(), fKeyOn, fConverter->faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

//---------------------------------------------------------------
// uiMidiKeyOff does scale (kLin/kLog/kExp) mapping for velocity
//---------------------------------------------------------------

class uiMidiKeyOff : public uiMidiTimedItem, public uiConverter {

    private:
        
        int fKeyOff;
  
    public:
    
        uiMidiKeyOff(midi* midi_out, int key, GUI* ui,
                     FAUSTFLOAT* zone,
                     FAUSTFLOAT min, FAUSTFLOAT max,
                     bool input = true,
                     MetaDataUI::Scale scale = MetaDataUI::kLin,
                     int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKeyOff(key)
        {}
        virtual ~uiMidiKeyOff()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyOff(rangeChan(), fKeyOff, fConverter->faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

//-----------------------------------------------------------------
// uiMidiKeyPress does scale (kLin/kLog/kExp) mapping for velocity
//-----------------------------------------------------------------

class uiMidiKeyPress : public uiMidiTimedItem, public uiConverter {

    private:
    
        int fKey;
  
    public:
    
        uiMidiKeyPress(midi* midi_out, int key, GUI* ui,
                       FAUSTFLOAT* zone,
                       FAUSTFLOAT min, FAUSTFLOAT max,
                       bool input = true,
                       MetaDataUI::Scale scale = MetaDataUI::kLin,
                       int chan = -1)
            :uiMidiTimedItem(midi_out, ui, zone, input, chan), uiConverter(scale, 0., 127., min, max), fKey(key)
        {}
        virtual ~uiMidiKeyPress()
        {}
        
        virtual void reflectZone()
        {
            FAUSTFLOAT v = *fZone;
            fCache = v;
            fMidiOut->keyPress(rangeChan(), fKey, fConverter->faust2ui(v));
        }
        
        void modifyZone(FAUSTFLOAT v)
        { 
            if (fInputCtrl) {
                uiItem::modifyZone(FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
        void modifyZone(double date, FAUSTFLOAT v)
        {
            if (fInputCtrl) {
                uiMidiTimedItem::modifyZone(date, FAUSTFLOAT(fConverter->ui2faust(v)));
            }
        }
    
};

/******************************************************************************************
 * MidiUI : Faust User Interface
 * This class decodes MIDI metadata and maps incoming MIDI messages to them.
 * Currently ctrl, keyon/keyoff, keypress, pgm, chanpress, pitchwheel/pitchbend
 * start/stop/clock meta data are handled.
 *
 * Maps associating MIDI event ID (like each ctrl number) with all MIDI aware UI items
 * are defined and progressively filled when decoding MIDI related metadata.
 * MIDI aware UI items are used in both directions:
 *  - modifying their internal state when receving MIDI input events
 *  - sending their internal state as MIDI output events
 *******************************************************************************************/

class MidiUI : public GUI, public midi, public MetaDataUI {

    // Add uiItem subclasses objects are deallocated by the inherited GUI class
    typedef std::map <int, std::vector<uiMidiCtrlChange*> > TCtrlChangeTable;
    typedef std::vector<uiMidiProgChange*>                  TProgChangeTable;
    typedef std::vector<uiMidiChanPress*>                   TChanPressTable;
    typedef std::map <int, std::vector<uiMidiKeyOn*> >      TKeyOnTable;
    typedef std::map <int, std::vector<uiMidiKeyOff*> >     TKeyOffTable;
    typedef std::map <int, std::vector<uiMidiKeyPress*> >   TKeyPressTable;
    typedef std::vector<uiMidiPitchWheel*>                  TPitchWheelTable;
    
    protected:
    
        TCtrlChangeTable fCtrlChangeTable;
        TProgChangeTable fProgChangeTable;
        TChanPressTable  fChanPressTable;
        TKeyOnTable      fKeyOnTable;
        TKeyOffTable     fKeyOffTable;
        TKeyOnTable      fKeyTable;
        TKeyPressTable   fKeyPressTable;
        TPitchWheelTable fPitchWheelTable;
        
        std::vector<uiMidiStart*> fStartTable;
        std::vector<uiMidiStop*>  fStopTable;
        std::vector<uiMidiClock*> fClockTable;
        
        std::vector<std::pair <std::string, std::string> > fMetaAux;
        
        midi_handler* fMidiHandler;
        bool fDelete;
        bool fTimeStamp;
    
        void addGenericZone(FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max, bool input = true)
        {
            if (fMetaAux.size() > 0) {
                for (size_t i = 0; i < fMetaAux.size(); i++) {
                    unsigned num;
                    unsigned chan;
                    if (fMetaAux[i].first == "midi") {
                        if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u %u", &num, &chan) == 2) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "ctrl %u", &num) == 1) {
                            fCtrlChangeTable[num].push_back(new uiMidiCtrlChange(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u %u", &num, &chan) == 2) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyon %u", &num) == 1) {
                            fKeyOnTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u %u", &num, &chan) == 2) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keyoff %u", &num) == 1) {
                            fKeyOffTable[num].push_back(new uiMidiKeyOff(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u %u", &num, &chan) == 2) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "key %u", &num) == 1) {
                            fKeyTable[num].push_back(new uiMidiKeyOn(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u %u", &num, &chan) == 2) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone), chan));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "keypress %u", &num) == 1) {
                            fKeyPressTable[num].push_back(new uiMidiKeyPress(fMidiHandler, num, this, zone, min, max, input, getScale(zone)));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "pgm %u", &chan) == 1) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input, chan));
                        } else if (strcmp(fMetaAux[i].second.c_str(), "pgm") == 0) {
                            fProgChangeTable.push_back(new uiMidiProgChange(fMidiHandler, this, zone, min, max, input));
                        } else if (gsscanf(fMetaAux[i].second.c_str(), "chanpress %u", &chan) == 1) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone), chan));
                        } else if ((fMetaAux[i].second == "chanpress")) {
                            fChanPressTable.push_back(new uiMidiChanPress(fMidiHandler, this, zone, min, max, input, getScale(zone)));
                        } else if ((gsscanf(fMetaAux[i].second.c_str(), "pitchwheel %u", &chan) == 1) || (gsscanf(fMetaAux[i].second.c_str(), "pitchbend %u", &chan) == 1)) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input, chan));
                        } else if ((fMetaAux[i].second == "pitchwheel") || (fMetaAux[i].second == "pitchbend")) {
                            fPitchWheelTable.push_back(new uiMidiPitchWheel(fMidiHandler, this, zone, min, max, input));
                        // MIDI sync
                        } else if (fMetaAux[i].second == "start") {
                            fStartTable.push_back(new uiMidiStart(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "stop") {
                            fStopTable.push_back(new uiMidiStop(fMidiHandler, this, zone, input));
                        } else if (fMetaAux[i].second == "clock") {
                            fClockTable.push_back(new uiMidiClock(fMidiHandler, this, zone, input));
                        // Explicit metadata to activate 'timestamp' mode
                        } else if (fMetaAux[i].second == "timestamp") {
                            fTimeStamp = true;
                        }
                    }
                }
            }
            fMetaAux.clear();
        }
    
        template <typename TABLE>
        void updateTable1(TABLE& table, double date, int channel, int val1)
        {
            for (size_t i = 0; i < table.size(); i++) {
                int channel_aux = table[i]->fChan;
                if (channel_aux == -1 || channel == channel_aux) {
                    if (fTimeStamp) {
                        table[i]->modifyZone(date, FAUSTFLOAT(val1));
                    } else {
                        table[i]->modifyZone(FAUSTFLOAT(val1));
                    }
                }
            }
        }
        
        template <typename TABLE>
        void updateTable2(TABLE& table, double date, int channel, int val1, int val2)
        {
            if (table.find(val1) != table.end()) {
                for (size_t i = 0; i < table[val1].size(); i++) {
                    int channel_aux = table[val1][i]->fChan;
                    if (channel_aux == -1 || channel == channel_aux) {
                        if (fTimeStamp) {
                            table[val1][i]->modifyZone(date, FAUSTFLOAT(val2));
                        } else {
                            table[val1][i]->modifyZone(FAUSTFLOAT(val2));
                        }
                    }
                }
            }
        }
    
    public:
    
        MidiUI(midi_handler* midi_handler, bool delete_handler = false)
        {
            fMidiHandler = midi_handler;
            fMidiHandler->addMidiIn(this);
            fDelete = delete_handler;
            fTimeStamp = false;
        }
 
        virtual ~MidiUI() 
        { 
            fMidiHandler->removeMidiIn(this);
            if (fDelete) delete fMidiHandler;
        }
    
        bool run() { return fMidiHandler->startMidi(); }
        void stop() { fMidiHandler->stopMidi(); }
        
        void addMidiIn(midi* midi_dsp) { fMidiHandler->addMidiIn(midi_dsp); }
        void removeMidiIn(midi* midi_dsp) { fMidiHandler->removeMidiIn(midi_dsp); }
      
        // -- active widgets
        
        virtual void addButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        virtual void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            addGenericZone(zone, FAUSTFLOAT(0), FAUSTFLOAT(1));
        }
        
        virtual void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }
        virtual void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step)
        {
            addGenericZone(zone, min, max);
        }

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max) 
        {
            addGenericZone(zone, min, max, false);
        }
        virtual void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max)
        {
            addGenericZone(zone, min, max, false);
        }

        // -- metadata declarations

        virtual void declare(FAUSTFLOAT* zone, const char* key, const char* val)
        {
            MetaDataUI::declare(zone, key, val);
            fMetaAux.push_back(std::make_pair(key, val));
        }
        
        // -- MIDI API
    
        void key(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyTable, date, channel, note, velocity);
        }
    
        MapUI* keyOn(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOnTable>(fKeyOnTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOn
            key(date, channel, note, velocity);
            return nullptr;
        }
        
        void keyOff(double date, int channel, int note, int velocity)
        {
            updateTable2<TKeyOffTable>(fKeyOffTable, date, channel, note, velocity);
            // If note is in fKeyTable, handle it as a keyOff with a 0 velocity
            key(date, channel, note, 0);
        }
        
        void ctrlChange(double date, int channel, int ctrl, int value)
        {
            updateTable2<TCtrlChangeTable>(fCtrlChangeTable, date, channel, ctrl, value);
        }
    
        void rpn(double date, int channel, int ctrl, int value)
        {
            if (ctrl == midi::PITCH_BEND_RANGE) {
                for (size_t i = 0; i < fPitchWheelTable.size(); i++) {
                    int channel_aux = fPitchWheelTable[i]->fChan;
                    if (channel_aux == -1 || channel == channel_aux) {
                        fPitchWheelTable[i]->setRange(value);
                    }
                }
            }
        }
    
        void progChange(double date, int channel, int pgm)
        {
            updateTable1<TProgChangeTable>(fProgChangeTable, date, channel, pgm);
        }
        
        void pitchWheel(double date, int channel, int wheel) 
        {
            updateTable1<TPitchWheelTable>(fPitchWheelTable, date, channel, wheel);
        }
        
        void keyPress(double date, int channel, int pitch, int press) 
        {
            updateTable2<TKeyPressTable>(fKeyPressTable, date, channel, pitch, press);
        }
        
        void chanPress(double date, int channel, int press)
        {
            updateTable1<TChanPressTable>(fChanPressTable, date, channel, press);
        }
        
        void ctrlChange14bits(double date, int channel, int ctrl, int value) {}
        
        // MIDI sync
        
        void startSync(double date)
        {
            for (size_t i = 0; i < fStartTable.size(); i++) {
                fStartTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
        
        void stopSync(double date)
        {
            for (size_t i = 0; i < fStopTable.size(); i++) {
                fStopTable[i]->modifyZone(date, FAUSTFLOAT(0));
            }
        }
        
        void clock(double date)
        {
            for (size_t i = 0; i < fClockTable.size(); i++) {
                fClockTable[i]->modifyZone(date, FAUSTFLOAT(1));
            }
        }
};

#endif // FAUST_MIDIUI_H
/**************************  END  MidiUI.h **************************/
/************************** BEGIN teensy-midi.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __teensy_midi__
#define __teensy_midi__

#include <iostream>
#include <cstdlib>

#include "Arduino.h"

extern usb_midi_class gUSBMIDI;

class teensy_midi : public midi_handler {
    
    public:
        
        void processMidi()
        {
            while (gUSBMIDI.read()) {
                
                int type = gUSBMIDI.getType();       // which MIDI message, 128-255
                int channel = gUSBMIDI.getChannel(); // which MIDI channel, 0-15
                double time = (double)gUSBMIDI.Clock;
                
                switch(type) {
                    case gUSBMIDI.Clock:
                        handleClock(time);
                        break;
                    case usbMIDI.Start:
                    // We can consider start and continue as identical messages
                    case usbMIDI.Continue:
                        handleStart(time);
                        break;
                    case gUSBMIDI.Stop:
                        handleStop(time);
                        break;
                    case gUSBMIDI.ProgramChange:
                        handleProgChange(time, channel, gUSBMIDI.getData1());
                        break;
                    case gUSBMIDI.AfterTouchChannel:
                        handleAfterTouch(time, channel, gUSBMIDI.getData1());
                        break;
                    case gUSBMIDI.NoteOff:
                        handleKeyOff(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                    case gUSBMIDI.NoteOn:
                        handleKeyOn(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                    case gUSBMIDI.ControlChange:
                        handleCtrlChange(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                    case gUSBMIDI.PitchBend:
                        handlePitchWheel(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                    case gUSBMIDI.AfterTouchPoly:
                        handlePolyAfterTouch(time, channel, gUSBMIDI.getData1(), gUSBMIDI.getData2());
                        break;
                }
            }
        }
};

#endif
/**************************  END  teensy-midi.h **************************/
#endif

// for polyphonic synths
#ifdef NVOICES
/************************** BEGIN poly-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __poly_dsp__
#define __poly_dsp__

#include <stdio.h>
#include <string>
#include <cmath>
#include <algorithm>
#include <functional>
#include <ostream>
#include <sstream>
#include <vector>
#include <limits.h>
#include <float.h>
#include <assert.h>

/************************** BEGIN dsp-combiner.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.

 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.

 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.

 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __dsp_combiner__
#define __dsp_combiner__

#include <string.h>
#include <string>
#include <assert.h>
#include <sstream>


// Base class and common code for binary combiners

class dsp_binary_combiner : public dsp {

    protected:

        dsp* fDSP1;
        dsp* fDSP2;

        void buildUserInterfaceAux(UI* ui_interface, const char* name)
        {
            ui_interface->openTabBox(name);
            ui_interface->openVerticalBox("DSP1");
            fDSP1->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->openVerticalBox("DSP2");
            fDSP2->buildUserInterface(ui_interface);
            ui_interface->closeBox();
            ui_interface->closeBox();
        }

        FAUSTFLOAT** allocateChannels(int num, int buffer_size)
        {
            FAUSTFLOAT** channels = new FAUSTFLOAT*[num];
            for (int chan = 0; chan < num; chan++) {
                channels[chan] = new FAUSTFLOAT[buffer_size];
                memset(channels[chan], 0, sizeof(FAUSTFLOAT) * buffer_size);
            }
            return channels;
        }

        void deleteChannels(FAUSTFLOAT** channels, int num)
        {
            for (int chan = 0; chan < num; chan++) {
                delete [] channels[chan];
            }
            delete [] channels;
        }

     public:

        dsp_binary_combiner(dsp* dsp1, dsp* dsp2):fDSP1(dsp1), fDSP2(dsp2)
        {}

        virtual ~dsp_binary_combiner()
        {
            delete fDSP1;
            delete fDSP2;
        }

        virtual int getSampleRate()
        {
            return fDSP1->getSampleRate();
        }
        virtual void init(int sample_rate)
        {
            fDSP1->init(sample_rate);
            fDSP2->init(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            fDSP1->instanceInit(sample_rate);
            fDSP2->instanceInit(sample_rate);
        }
        virtual void instanceConstants(int sample_rate)
        {
            fDSP1->instanceConstants(sample_rate);
            fDSP2->instanceConstants(sample_rate);
        }

        virtual void instanceResetUserInterface()
        {
            fDSP1->instanceResetUserInterface();
            fDSP2->instanceResetUserInterface();
        }

        virtual void instanceClear()
        {
            fDSP1->instanceClear();
            fDSP2->instanceClear();
        }

        virtual void metadata(Meta* m)
        {
            fDSP1->metadata(m);
            fDSP2->metadata(m);
        }

};

// Combine two 'compatible' DSP in sequence

class dsp_sequencer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;

    public:

        dsp_sequencer(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs(), buffer_size);
        }

        virtual ~dsp_sequencer()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface, "Sequencer");
        }

        virtual dsp* clone()
        {
            return new dsp_sequencer(fDSP1->clone(), fDSP2->clone());
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);
            fDSP2->compute(count, fDSP1Outputs, outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two DSP in parallel

class dsp_parallelizer : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_parallelizer(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
            fDSP2Outputs = new FAUSTFLOAT*[fDSP2->getNumOutputs()];
        }

        virtual ~dsp_parallelizer()
        {
            delete [] fDSP2Inputs;
            delete [] fDSP2Outputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() + fDSP2->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs() + fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface, "Parallelizer");
        }

        virtual dsp* clone()
        {
            return new dsp_parallelizer(fDSP1->clone(), fDSP2->clone());
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, outputs);

            // Shift inputs/outputs channels for fDSP2
            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                fDSP2Inputs[chan] = inputs[fDSP1->getNumInputs() + chan];
            }
            for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                fDSP2Outputs[chan] = outputs[fDSP1->getNumOutputs() + chan];
            }

            fDSP2->compute(count, fDSP2Inputs, fDSP2Outputs);
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

// Combine two 'compatible' DSP in splitter

class dsp_splitter : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

    public:

        dsp_splitter(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs(), buffer_size);
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_splitter()
        {
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface, "Splitter");
        }

        virtual dsp* clone()
        {
            return new dsp_splitter(fDSP1->clone(), fDSP2->clone());
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, inputs, fDSP1Outputs);

            for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                 fDSP2Inputs[chan] = fDSP1Outputs[chan % fDSP1->getNumOutputs()];
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in merger

class dsp_merger : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;
        FAUSTFLOAT** fDSP2Inputs;

        void mix(int count, FAUSTFLOAT* dst, FAUSTFLOAT* src)
        {
            for (int frame = 0; frame < count; frame++) {
                dst[frame] += src[frame];
            }
        }

    public:

        dsp_merger(dsp* dsp1, dsp* dsp2, int buffer_size = 4096):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs(), buffer_size);
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs(), buffer_size);
            fDSP2Inputs = new FAUSTFLOAT*[fDSP2->getNumInputs()];
        }

        virtual ~dsp_merger()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            delete [] fDSP2Inputs;
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs(); }
        virtual int getNumOutputs() { return fDSP2->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface, "Merge");
        }

        virtual dsp* clone()
        {
            return new dsp_merger(fDSP1->clone(), fDSP2->clone());
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            fDSP1->compute(count, fDSP1Inputs, fDSP1Outputs);

            memset(fDSP2Inputs, 0, sizeof(FAUSTFLOAT*) * fDSP2->getNumInputs());

            for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                int mchan = chan % fDSP2->getNumInputs();
                if (fDSP2Inputs[mchan]) {
                    mix(count, fDSP2Inputs[mchan], fDSP1Outputs[chan]);
                } else {
                    fDSP2Inputs[mchan] = fDSP1Outputs[chan];
                }
            }

            fDSP2->compute(count, fDSP2Inputs, outputs);
        }
};

// Combine two 'compatible' DSP in a recursive way

class dsp_recursiver : public dsp_binary_combiner {

    private:

        FAUSTFLOAT** fDSP1Inputs;
        FAUSTFLOAT** fDSP1Outputs;

        FAUSTFLOAT** fDSP2Inputs;
        FAUSTFLOAT** fDSP2Outputs;

    public:

        dsp_recursiver(dsp* dsp1, dsp* dsp2):dsp_binary_combiner(dsp1, dsp2)
        {
            fDSP1Inputs = allocateChannels(fDSP1->getNumInputs(), 1);
            fDSP1Outputs = allocateChannels(fDSP1->getNumOutputs(), 1);
            fDSP2Inputs = allocateChannels(fDSP2->getNumInputs(), 1);
            fDSP2Outputs = allocateChannels(fDSP2->getNumOutputs(), 1);
        }

        virtual ~dsp_recursiver()
        {
            deleteChannels(fDSP1Inputs, fDSP1->getNumInputs());
            deleteChannels(fDSP1Outputs, fDSP1->getNumOutputs());
            deleteChannels(fDSP2Inputs, fDSP2->getNumInputs());
            deleteChannels(fDSP2Outputs, fDSP2->getNumOutputs());
        }

        virtual int getNumInputs() { return fDSP1->getNumInputs() - fDSP2->getNumOutputs(); }
        virtual int getNumOutputs() { return fDSP1->getNumOutputs(); }

        virtual void buildUserInterface(UI* ui_interface)
        {
            buildUserInterfaceAux(ui_interface, "Recursiver");
        }

        virtual dsp* clone()
        {
            return new dsp_recursiver(fDSP1->clone(), fDSP2->clone());
        }

        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            for (int frame = 0; (frame < count); frame++) {

                for (int chan = 0; chan < fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan][0] = fDSP2Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP1->getNumInputs() - fDSP2->getNumOutputs(); chan++) {
                    fDSP1Inputs[chan + fDSP2->getNumOutputs()][0] = inputs[chan][frame];
                }

                fDSP1->compute(1, fDSP1Inputs, fDSP1Outputs);

                for (int chan = 0; chan < fDSP1->getNumOutputs(); chan++) {
                    outputs[chan][frame] = fDSP1Outputs[chan][0];
                }

                for (int chan = 0; chan < fDSP2->getNumInputs(); chan++) {
                    fDSP2Inputs[chan][0] = fDSP1Outputs[chan][0];
                }

                fDSP2->compute(1, fDSP2Inputs, fDSP2Outputs);
            }
        }

        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) { compute(count, inputs, outputs); }

};

#ifndef __dsp_algebra_api__
#define __dsp_algebra_api__
// DSP algebra API
/*
 Each operation takes two DSP as parameters, returns the combined DSPs, or null if failure with an error message.
 */

static dsp* createDSPSequencer(dsp* dsp1, dsp* dsp2, std::string& error)
{
    if (dsp1->getNumOutputs() != dsp2->getNumInputs()) {
        std::stringstream error_aux;
        error_aux << "Connection error int dsp_sequencer : the number of outputs ("
                  << dsp1->getNumOutputs() << ") of A "
                  << "must be equal to the number of inputs (" << dsp2->getNumInputs() << ") of B" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_sequencer(dsp1, dsp2);
    }
}

static dsp* createDSPParallelizer(dsp* dsp1, dsp* dsp2, std::string& error)
{
    return new dsp_parallelizer(dsp1, dsp2);
}

static dsp* createDSPSplitter(dsp* dsp1, dsp* dsp2, std::string& error)
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_splitter : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_splitter : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() % dsp1->getNumOutputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_splitter : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a divisor of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2);
    } else {
        return new dsp_splitter(dsp1, dsp2);
    }
}

static dsp* createDSPMerger(dsp* dsp1, dsp* dsp2, std::string& error)
{
    if (dsp1->getNumOutputs() == 0) {
        error = "Connection error in dsp_merger : the first expression has no outputs\n";
        return nullptr;
    } else if (dsp2->getNumInputs() == 0) {
        error = "Connection error in dsp_merger : the second expression has no inputs\n";
        return nullptr;
    } else if (dsp1->getNumOutputs() % dsp2->getNumInputs() != 0) {
        std::stringstream error_aux;
        error_aux << "Connection error in dsp_merger : the number of outputs (" << dsp1->getNumOutputs()
                  << ") of the first expression should be a multiple of the number of inputs ("
                  << dsp2->getNumInputs()
                  << ") of the second expression" << std::endl;
        error = error_aux.str();
        return nullptr;
    } else if (dsp2->getNumInputs() == dsp1->getNumOutputs()) {
        return new dsp_sequencer(dsp1, dsp2);
    } else {
        return new dsp_merger(dsp1, dsp2);
    }
}

static dsp* createDSPRecursiver(dsp* dsp1, dsp* dsp2, std::string& error)
{
    if ((dsp2->getNumInputs() > dsp1->getNumOutputs()) || (dsp2->getNumOutputs() > dsp1->getNumInputs())) {
        std::stringstream error_aux;
        error_aux << "Connection error in : dsp_recursiver" << std::endl;
        if (dsp2->getNumInputs() > dsp1->getNumOutputs()) {
            error_aux << "The number of outputs " << dsp1->getNumOutputs()
                      << " of the first expression should be greater or equal to the number of inputs ("
                      << dsp2->getNumInputs()
                      << ") of the second expression" << std::endl;
        }
        if (dsp2->getNumOutputs() > dsp1->getNumInputs()) {
            error_aux << "The number of inputs " << dsp1->getNumInputs()
                      << " of the first expression should be greater or equal to the number of outputs ("
                      << dsp2->getNumOutputs()
                      << ") of the second expression" << std::endl;
        }
        error = error_aux.str();
        return nullptr;
    } else {
        return new dsp_recursiver(dsp1, dsp2);
    }
}
#endif

#endif
/**************************  END  dsp-combiner.h **************************/
/************************** BEGIN proxy-dsp.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2017 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __proxy_dsp__
#define __proxy_dsp__

#include <vector>
#include <map>

/************************** BEGIN JSONUIDecoder.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2003-2020 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JSONUIDecoder__
#define __JSONUIDecoder__

#include <vector>
#include <map>
#include <utility>
#include <cstdlib>
#include <sstream>
#include <functional>

/************************** BEGIN CGlue.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef CGLUE_H
#define CGLUE_H

/************************** BEGIN CInterface.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2018 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef CINTERFACE_H
#define CINTERFACE_H

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

#include <stdlib.h>

#ifdef __cplusplus
extern "C" {
#endif
    
struct Soundfile;

/*******************************************************************************
 * UI, Meta and MemoryManager structures for C code.
 ******************************************************************************/

// -- widget's layouts

typedef void (* openTabBoxFun) (void* ui_interface, const char* label);
typedef void (* openHorizontalBoxFun) (void* ui_interface, const char* label);
typedef void (* openVerticalBoxFun) (void* ui_interface, const char* label);
typedef void (* closeBoxFun) (void* ui_interface);

// -- active widgets

typedef void (* addButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addCheckButtonFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone);
typedef void (* addVerticalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addHorizontalSliderFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);
typedef void (* addNumEntryFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT min, FAUSTFLOAT max, FAUSTFLOAT step);

// -- passive widgets

typedef void (* addHorizontalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);
typedef void (* addVerticalBargraphFun) (void* ui_interface, const char* label, FAUSTFLOAT* zone, FAUSTFLOAT min, FAUSTFLOAT max);

// -- soundfiles
    
typedef void (* addSoundfileFun) (void* ui_interface, const char* label, const char* url, struct Soundfile** sf_zone);

typedef void (* declareFun) (void* ui_interface, FAUSTFLOAT* zone, const char* key, const char* value);

typedef struct {

    void* uiInterface;

    openTabBoxFun openTabBox;
    openHorizontalBoxFun openHorizontalBox;
    openVerticalBoxFun openVerticalBox;
    closeBoxFun closeBox;
    addButtonFun addButton;
    addCheckButtonFun addCheckButton;
    addVerticalSliderFun addVerticalSlider;
    addHorizontalSliderFun addHorizontalSlider;
    addNumEntryFun addNumEntry;
    addHorizontalBargraphFun addHorizontalBargraph;
    addVerticalBargraphFun addVerticalBargraph;
    addSoundfileFun addSoundfile;
    declareFun declare;

} UIGlue;

typedef void (* metaDeclareFun) (void* ui_interface, const char* key, const char* value);

typedef struct {

    void* metaInterface;
    
    metaDeclareFun declare;

} MetaGlue;

/***************************************
 *  Interface for the DSP object
 ***************************************/

typedef char dsp_imp;
    
typedef dsp_imp* (* newDspFun) ();
typedef void (* destroyDspFun) (dsp_imp* dsp);
typedef int (* getNumInputsFun) (dsp_imp* dsp);
typedef int (* getNumOutputsFun) (dsp_imp* dsp);
typedef void (* buildUserInterfaceFun) (dsp_imp* dsp, UIGlue* ui);
typedef int (* getSampleRateFun) (dsp_imp* dsp);
typedef void (* initFun) (dsp_imp* dsp, int sample_rate);
typedef void (* classInitFun) (int sample_rate);
typedef void (* instanceInitFun) (dsp_imp* dsp, int sample_rate);
typedef void (* instanceConstantsFun) (dsp_imp* dsp, int sample_rate);
typedef void (* instanceResetUserInterfaceFun) (dsp_imp* dsp);
typedef void (* instanceClearFun) (dsp_imp* dsp);
typedef void (* computeFun) (dsp_imp* dsp, int len, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs);
typedef void (* metadataFun) (MetaGlue* meta);
    
/***************************************
 * DSP memory manager functions
 ***************************************/

typedef void* (* allocateFun) (void* manager_interface, size_t size);
typedef void (* destroyFun) (void* manager_interface, void* ptr);

typedef struct {
    
    void* managerInterface;
    
    allocateFun allocate;
    destroyFun destroy;
    
} MemoryManagerGlue;

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CInterface.h **************************/

#ifdef __cplusplus
extern "C" {
#endif

/*******************************************************************************
 * UI glue code
 ******************************************************************************/
 
class UIFloat
{

    public:

        UIFloat() {}

        virtual ~UIFloat() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, float* zone) = 0;
        virtual void addCheckButton(const char* label, float* zone) = 0;
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step) = 0;
        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) = 0;
        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(float* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueFloat(void* cpp_interface, const char* label)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueFloat(void* cpp_interface)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueFloat(void* cpp_interface, const char* label, float* zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueFloat(void* cpp_interface, const char* label, float* zone, float init, float min, float max, float step)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueFloat(void* cpp_interface, const char* label, float* zone, float min, float max)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueFloat(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueFloat(void* cpp_interface, float* zone, const char* key, const char* value)
{
    UIFloat* ui_interface = static_cast<UIFloat*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

class UIDouble
{

    public:

        UIDouble() {}

        virtual ~UIDouble() {}

        // -- widget's layouts

        virtual void openTabBox(const char* label) = 0;
        virtual void openHorizontalBox(const char* label) = 0;
        virtual void openVerticalBox(const char* label) = 0;
        virtual void closeBox() = 0;

        // -- active widgets

        virtual void addButton(const char* label, double* zone) = 0;
        virtual void addCheckButton(const char* label, double* zone) = 0;
        virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step) = 0;
        virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step) = 0;

        // -- passive widgets

        virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max) = 0;
        virtual void addVerticalBargraph(const char* label, double* zone, double min, double max) = 0;
    
        // -- soundfiles
    
        virtual void addSoundfile(const char* label, const char* filename, Soundfile** sf_zone) = 0;

        // -- metadata declarations

        virtual void declare(double* zone, const char* key, const char* val) {}
};

static void openTabBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openTabBox(label);
}

static void openHorizontalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openHorizontalBox(label);
}

static void openVerticalBoxGlueDouble(void* cpp_interface, const char* label)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->openVerticalBox(label);
}

static void closeBoxGlueDouble(void* cpp_interface)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->closeBox();
}

static void addButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addButton(label, zone);
}

static void addCheckButtonGlueDouble(void* cpp_interface, const char* label, double* zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addCheckButton(label, zone);
}

static void addVerticalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalSlider(label, zone, init, min, max, step);
}

static void addHorizontalSliderGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalSlider(label, zone, init, min, max, step);
}

static void addNumEntryGlueDouble(void* cpp_interface, const char* label, double* zone, double init, double min, double max, double step)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addNumEntry(label, zone, init, min, max, step);
}

static void addHorizontalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addHorizontalBargraph(label, zone, min, max);
}

static void addVerticalBargraphGlueDouble(void* cpp_interface, const char* label, double* zone, double min, double max)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addVerticalBargraph(label, zone, min, max);
}
    
static void addSoundfileGlueDouble(void* cpp_interface, const char* label, const char* url, Soundfile** sf_zone)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->addSoundfile(label, url, sf_zone);
}

static void declareGlueDouble(void* cpp_interface, double* zone, const char* key, const char* value)
{
    UIDouble* ui_interface = static_cast<UIDouble*>(cpp_interface);
    ui_interface->declare(zone, key, value);
}

static void buildUIGlue(UIGlue* glue, UI* ui_interface, bool is_double)
{
    glue->uiInterface = ui_interface;
    
    if (is_double) {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueDouble);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueDouble);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueDouble);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueDouble);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueDouble);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueDouble);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueDouble);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueDouble);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueDouble);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueDouble);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueDouble);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueDouble);
        glue->declare = reinterpret_cast<declareFun>(declareGlueDouble);
    } else {
        glue->openTabBox = reinterpret_cast<openTabBoxFun>(openTabBoxGlueFloat);
        glue->openHorizontalBox = reinterpret_cast<openHorizontalBoxFun>(openHorizontalBoxGlueFloat);
        glue->openVerticalBox = reinterpret_cast<openVerticalBoxFun>(openVerticalBoxGlueFloat);
        glue->closeBox = reinterpret_cast<closeBoxFun>(closeBoxGlueFloat);
        glue->addButton = reinterpret_cast<addButtonFun>(addButtonGlueFloat);
        glue->addCheckButton = reinterpret_cast<addCheckButtonFun>(addCheckButtonGlueFloat);
        glue->addVerticalSlider = reinterpret_cast<addVerticalSliderFun>(addVerticalSliderGlueFloat);
        glue->addHorizontalSlider = reinterpret_cast<addHorizontalSliderFun>(addHorizontalSliderGlueFloat);
        glue->addNumEntry = reinterpret_cast<addNumEntryFun>(addNumEntryGlueFloat);
        glue->addHorizontalBargraph = reinterpret_cast<addHorizontalBargraphFun>(addHorizontalBargraphGlueFloat);
        glue->addVerticalBargraph = reinterpret_cast<addVerticalBargraphFun>(addVerticalBargraphGlueFloat);
        glue->addSoundfile = reinterpret_cast<addSoundfileFun>(addSoundfileGlueFloat);
        glue->declare = reinterpret_cast<declareFun>(declareGlueFloat);
    }
}
    
class UITemplate
{
    
    private:
        
        void* fCPPInterface;
        
    public:
        
        UITemplate(void* cpp_interface):fCPPInterface(cpp_interface)
        {}
        
        virtual ~UITemplate() {}
        
        // -- widget's layouts
        
        virtual void openTabBox(const char* label)
        {
            openTabBoxGlueFloat(fCPPInterface, label);
        }
        virtual void openHorizontalBox(const char* label)
        {
            openHorizontalBoxGlueFloat(fCPPInterface, label);
        }
        virtual void openVerticalBox(const char* label)
        {
            openVerticalBoxGlueFloat(fCPPInterface, label);
        }
        virtual void closeBox()
        {
            closeBoxGlueFloat(fCPPInterface);
        }
        
        // float version
        
        // -- active widgets
        
        virtual void addButton(const char* label, float* zone)
        {
            addButtonGlueFloat(fCPPInterface, label, zone);
        }
        virtual void addCheckButton(const char* label, float* zone)
        {
            addCheckButtonGlueFloat(fCPPInterface, label, zone);
        }
        
        virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)
        {
            addVerticalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
        }
        
        virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
        {
            addHorizontalSliderGlueFloat(fCPPInterface, label, zone, init, min, max, step);
        }
        
        virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
        {
            addNumEntryGlueFloat(fCPPInterface, label, zone, init, min, max, step);
        }
        
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max)
        {
            addHorizontalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
        }
        
        virtual void addVerticalBargraph(const char* label, float* zone, float min, float max)
        {
            addVerticalBargraphGlueFloat(fCPPInterface, label, zone, min, max);
        }
    
        // -- metadata declarations
        
        virtual void declare(float* zone, const char* key, const char* val)
        {
            declareGlueFloat(fCPPInterface, zone, key, val);
        }
        
        // double version
        
        virtual void addButton(const char* label, double* zone)
        {
            addButtonGlueDouble(fCPPInterface, label, zone);
        }
        virtual void addCheckButton(const char* label, double* zone)
        {
            addCheckButtonGlueDouble(fCPPInterface, label, zone);
        }
        
        virtual void addVerticalSlider(const char* label, double* zone, double init, double min, double max, double step)
        {
            addVerticalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
        }
        
        virtual void addHorizontalSlider(const char* label, double* zone, double init, double min, double max, double step)
        {
            addHorizontalSliderGlueDouble(fCPPInterface, label, zone, init, min, max, step);
        }
        
        virtual void addNumEntry(const char* label, double* zone, double init, double min, double max, double step)
        {
            addNumEntryGlueDouble(fCPPInterface, label, zone, init, min, max, step);
        }
    
        // -- soundfiles
        
        virtual void addSoundfile(const char* label, const char* url, Soundfile** sf_zone)
        {
            addSoundfileGlueFloat(fCPPInterface, label, url, sf_zone);
        }
    
        // -- passive widgets
        
        virtual void addHorizontalBargraph(const char* label, double* zone, double min, double max)
        {
            addHorizontalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
        }
        
        virtual void addVerticalBargraph(const char* label, double* zone, double min, double max)
        {
            addVerticalBargraphGlueDouble(fCPPInterface, label, zone, min, max);
        }
    
        // -- metadata declarations
        
        virtual void declare(double* zone, const char* key, const char* val)
        {
            declareGlueDouble(fCPPInterface, zone, key, val);
        }

};

/*******************************************************************************
 * Meta glue code
 ******************************************************************************/

static void declareMetaGlue(void* cpp_interface, const char* key, const char* value)
{
    Meta* meta_interface = static_cast<Meta*>(cpp_interface);
    meta_interface->declare(key, value);
}

static void buildMetaGlue(MetaGlue* glue, Meta* meta)
{
    glue->metaInterface = meta;
    glue->declare = declareMetaGlue;
}
    
/*******************************************************************************
 * Memory manager glue code
 ******************************************************************************/

static void* allocateMemoryManagerGlue(void* cpp_interface, size_t size)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    return manager_interface->allocate(size);
}
    
static void destroyMemoryManagerGlue(void* cpp_interface, void* ptr)
{
    dsp_memory_manager* manager_interface = static_cast<dsp_memory_manager*>(cpp_interface);
    manager_interface->destroy(ptr);
}

static void buildManagerGlue(MemoryManagerGlue* glue, dsp_memory_manager* manager)
{
    glue->managerInterface = manager;
    glue->allocate = allocateMemoryManagerGlue;
    glue->destroy = destroyMemoryManagerGlue;
}

#ifdef __cplusplus
}
#endif

#endif
/**************************  END  CGlue.h **************************/

#ifdef _WIN32
#include <windows.h>
#define snprintf _snprintf
#endif

//-------------------------------------------------------------------
//  Decode a dsp JSON description and implement 'buildUserInterface'
//-------------------------------------------------------------------

#define REAL_UI(ui_interface) reinterpret_cast<UIReal<REAL>*>(ui_interface)
#define REAL_ADR(offset)      reinterpret_cast<REAL*>(&memory_block[offset])
#define REAL_EXT_ADR(offset)  reinterpret_cast<FAUSTFLOAT*>(&memory_block[offset])
#define SOUNDFILE_ADR(offset) reinterpret_cast<Soundfile**>(&memory_block[offset])

typedef std::function<void(double)> ReflectFunction;
typedef std::function<double()> ModifyFunction;

struct ExtZoneParam {

    virtual void reflectZone() = 0;
    virtual void modifyZone() = 0;
    
    virtual void setReflectZoneFun(ReflectFunction reflect) = 0;
    virtual void setModifyZoneFun(ModifyFunction modify) = 0;
    
    virtual ~ExtZoneParam()
    {}
    
};

template <typename REAL>
struct JSONUIDecoderReal {
    
    struct ZoneParam : public ExtZoneParam {
        
        REAL fZone;
        int fIndex;
        ReflectFunction fReflect;
        ModifyFunction fModify;
        
    #if defined(TARGET_OS_IPHONE) || defined(WIN32)
        ZoneParam(int index, ReflectFunction reflect = nullptr, ModifyFunction modify = nullptr)
        :fIndex(index), fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { if (fReflect) fReflect(fZone); }
        void modifyZone() { if (fModify) fZone = fModify(); }
    #else
        ZoneParam(int index, ReflectFunction reflect = [](REAL value) {}, ModifyFunction modify = []() { return REAL(-1); })
        :fIndex(index), fReflect(reflect), fModify(modify)
        {}
        void reflectZone() { fReflect(fZone); }
        void modifyZone() { fZone = fModify(); }
    #endif
        
        void setReflectZoneFun(ReflectFunction reflect) { fReflect = reflect; }
        void setModifyZoneFun(ModifyFunction modify) { fModify = modify; }
        
    };

    typedef std::vector<ExtZoneParam*> controlMap;
  
    std::string fName;
    std::string fFileName;
    std::string fJSON;
    std::string fVersion;
    std::string fCompileOptions;
    
    std::map<std::string, std::string> fMetadata;
    std::vector<itemInfo> fUiItems;
    
    std::vector<std::string> fLibraryList;
    std::vector<std::string> fIncludePathnames;
    
    Soundfile** fSoundfiles;
    
    int fNumInputs, fNumOutputs, fSRIndex;
    int fSoundfileItems;
    int fDSPSize;
    
    controlMap fPathInputTable;     // [path, ZoneParam]
    controlMap fPathOutputTable;    // [path, ZoneParam]

    bool isInput(const std::string& type)
    {
        return (type == "vslider" || type == "hslider" || type == "nentry" || type == "button" || type == "checkbox");
    }
    bool isOutput(const std::string& type) { return (type == "hbargraph" || type == "vbargraph"); }
    bool isSoundfile(const std::string& type) { return (type == "soundfile"); }
    
    std::string getString(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? map[key].first : "";
    }
    
    int getInt(std::map<std::string, std::pair<std::string, double> >& map, const std::string& key)
    {
        return (map.find(key) != map.end()) ? int(map[key].second) : -1;
    }
    
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        fPathInputTable[index]->setReflectZoneFun(fun);
    }
    
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        fPathOutputTable[index]->setModifyZoneFun(fun);
    }

    JSONUIDecoderReal(const std::string& json)
    {
        fJSON = json;
        const char* p = fJSON.c_str();
        std::map<std::string, std::pair<std::string, double> > meta_data1;
        std::map<std::string, std::vector<std::string> > meta_data2;
        parseJson(p, meta_data1, fMetadata, meta_data2, fUiItems);
        
        // meta_data1 contains <name : val>, <inputs : val>, <ouputs : val> pairs etc...
        fName = getString(meta_data1, "name");
        fFileName = getString(meta_data1, "filename");
        fVersion = getString(meta_data1, "version");
        fCompileOptions = getString(meta_data1, "compile_options");
        
        if (meta_data2.find("library_list") != meta_data2.end()) {
            fLibraryList = meta_data2["library_list"];
        }
        if (meta_data2.find("include_pathnames") != meta_data2.end()) {
            fIncludePathnames = meta_data2["include_pathnames"];
        }
        
        fDSPSize = getInt(meta_data1, "size");
        fNumInputs = getInt(meta_data1, "inputs");
        fNumOutputs = getInt(meta_data1, "outputs");
        fSRIndex = getInt(meta_data1, "sr_index");
       
        fSoundfileItems = 0;
        for (auto& it : fUiItems) {
            std::string type = it.type;
            if (isSoundfile(type)) {
                fSoundfileItems++;
            }
        }
        
        fSoundfiles = new Soundfile*[fSoundfileItems];
        
        // Prepare the fPathTable and init zone
        for (auto& it : fUiItems) {
            std::string type = it.type;
            // Meta data declaration for input items
            if (isInput(type)) {
                ZoneParam* param = new ZoneParam(it.index);
                fPathInputTable.push_back(param);
                param->fZone = it.init;
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                ZoneParam* param = new ZoneParam(it.index);
                fPathOutputTable.push_back(param);
                param->fZone = REAL(0);
            }
        }
    }
    
    virtual ~JSONUIDecoderReal()
    {
        delete [] fSoundfiles;
        for (auto& it : fPathInputTable) {
            delete it;
        }
        for (auto& it : fPathOutputTable) {
            delete it;
        }
    }
    
    void metadata(Meta* m)
    {
        for (auto& it : fMetadata) {
            m->declare(it.first.c_str(), it.second.c_str());
        }
    }
    
    void metadata(MetaGlue* m)
    {
        for (auto& it : fMetadata) {
            m->declare(m->metaInterface, it.first.c_str(), it.second.c_str());
        }
    }
    
    void resetUserInterface()
    {
        int item = 0;
        for (auto& it : fUiItems) {
            if (isInput(it.type)) {
                static_cast<ZoneParam*>(fPathInputTable[item++])->fZone = it.init;
            }
        }
    }
    
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        for (auto& it : fUiItems) {
            int offset = it.index;
            if (isInput(it.type)) {
                *REAL_ADR(offset) = it.init;
            } else if (isSoundfile(it.type)) {
                if (*SOUNDFILE_ADR(offset) == nullptr) {
                    *SOUNDFILE_ADR(offset) = defaultsound;
                }
            }
        }
    }
    
    int getSampleRate(char* memory_block)
    {
        return *reinterpret_cast<int*>(&memory_block[fSRIndex]);
    }
   
    void buildUserInterface(UI* ui_interface)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        int countIn = 0;
        int countOut = 0;
        int countSound = 0;
        
        for (auto& it : fUiItems) {
            
            std::string type = it.type;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(&static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(&static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") { 
                REAL_UI(ui_interface)->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), &fSoundfiles[countSound]);
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), &static_cast<ZoneParam*>(fPathOutputTable[countOut])->fZone, min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone, init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), &static_cast<ZoneParam*>(fPathInputTable[countIn])->fZone);
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
            
            if (isInput(type)) {
                countIn++;
            } else if (isOutput(type)) {
                countOut++;
            } else if (isSoundfile(type)) {
                countSound++;
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (auto& it : fUiItems) {
            
            std::string type = it.type;
            int offset = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(REAL_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    REAL_UI(ui_interface)->declare(0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                REAL_UI(ui_interface)->openHorizontalBox(it.label.c_str());
            } else if (type == "vgroup") {
                REAL_UI(ui_interface)->openVerticalBox(it.label.c_str());
            } else if (type == "tgroup") {
                REAL_UI(ui_interface)->openTabBox(it.label.c_str());
            } else if (type == "vslider") {
                REAL_UI(ui_interface)->addVerticalSlider(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "hslider") {
                REAL_UI(ui_interface)->addHorizontalSlider(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "checkbox") {
                REAL_UI(ui_interface)->addCheckButton(it.label.c_str(), REAL_ADR(offset));
            } else if (type == "soundfile") {
                REAL_UI(ui_interface)->addSoundfile(it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(offset));
            } else if (type == "hbargraph") {
                REAL_UI(ui_interface)->addHorizontalBargraph(it.label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "vbargraph") {
                REAL_UI(ui_interface)->addVerticalBargraph(it.label.c_str(), REAL_ADR(offset), min, max);
            } else if (type == "nentry") {
                REAL_UI(ui_interface)->addNumEntry(it.label.c_str(), REAL_ADR(offset), init, min, max, step);
            } else if (type == "button") {
                REAL_UI(ui_interface)->addButton(it.label.c_str(), REAL_ADR(offset));
            } else if (type == "close") {
                REAL_UI(ui_interface)->closeBox();
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        // MANDATORY: to be sure floats or double are correctly parsed
        char* tmp_local = setlocale(LC_ALL, nullptr);
        if (tmp_local != NULL) {
            tmp_local = strdup(tmp_local);
        }
        setlocale(LC_ALL, "C");
        
        for (auto& it : fUiItems) {
            
            std::string type = it.type;
            int offset = it.index;
            REAL init = REAL(it.init);
            REAL min = REAL(it.fmin);
            REAL max = REAL(it.fmax);
            REAL step = REAL(it.step);
            
            // Meta data declaration for input items
            if (isInput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for output items
            else if (isOutput(type)) {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, REAL_EXT_ADR(offset), it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            // Meta data declaration for group opening or closing
            else {
                for (size_t i = 0; i < it.meta.size(); i++) {
                    ui_interface->declare(ui_interface->uiInterface, 0, it.meta[i].first.c_str(), it.meta[i].second.c_str());
                }
            }
            
            if (type == "hgroup") {
                ui_interface->openHorizontalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vgroup") {
                ui_interface->openVerticalBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "tgroup") {
                ui_interface->openTabBox(ui_interface->uiInterface, it.label.c_str());
            } else if (type == "vslider") {
                ui_interface->addVerticalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), init, min, max, step);
            } else if (type == "hslider") {
                ui_interface->addHorizontalSlider(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), init, min, max, step);
            } else if (type == "checkbox") {
                ui_interface->addCheckButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset));
            } else if (type == "soundfile") {
                ui_interface->addSoundfile(ui_interface->uiInterface, it.label.c_str(), it.url.c_str(), SOUNDFILE_ADR(offset));
            } else if (type == "hbargraph") {
                ui_interface->addHorizontalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), min, max);
            } else if (type == "vbargraph") {
                ui_interface->addVerticalBargraph(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), min, max);
            } else if (type == "nentry") {
                ui_interface->addNumEntry(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset), init, min, max, step);
            } else if (type == "button") {
                ui_interface->addButton(ui_interface->uiInterface, it.label.c_str(), REAL_EXT_ADR(offset));
            } else if (type == "close") {
                ui_interface->closeBox(ui_interface->uiInterface);
            }
        }
        
        if (tmp_local != NULL) {
            setlocale(LC_ALL, tmp_local);
            free(tmp_local);
        }
    }
    
    bool hasCompileOption(const std::string& option)
    {
        std::istringstream iss(fCompileOptions);
        std::string token;
        while (std::getline(iss, token, ' ')) {
            if (token == option) return true;
        }
        return false;
    }
    
};

// Templated decoder

struct JSONUITemplatedDecoder
{

    virtual ~JSONUITemplatedDecoder()
    {}
    
    virtual void metadata(Meta* m) = 0;
    virtual void metadata(MetaGlue* glue) = 0;
    virtual int getDSPSize() = 0;
    virtual std::string getName() = 0;
    virtual std::string getLibVersion() = 0;
    virtual std::string getCompileOptions() = 0;
    virtual std::vector<std::string> getLibraryList() = 0;
    virtual std::vector<std::string> getIncludePathnames() = 0;
    virtual int getNumInputs() = 0;
    virtual int getNumOutputs() = 0;
    virtual int getSampleRate(char* memory_block) = 0;
    virtual void setReflectZoneFun(int index, ReflectFunction fun) = 0;
    virtual void setModifyZoneFun(int index, ModifyFunction fun) = 0;
    virtual std::vector<ExtZoneParam*>& getInputControls() = 0;
    virtual std::vector<ExtZoneParam*>& getOutputControls() = 0;
    virtual void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr) = 0;
    virtual void buildUserInterface(UI* ui_interface) = 0;
    virtual void buildUserInterface(UI* ui_interface, char* memory_block) = 0;
    virtual void buildUserInterface(UIGlue* ui_interface, char* memory_block) = 0;
    virtual bool hasCompileOption(const std::string& option) = 0;
};

// Float templated decoder

struct JSONUIFloatDecoder : public JSONUIDecoderReal<float>, public JSONUITemplatedDecoder
{
    JSONUIFloatDecoder(const std::string& json):JSONUIDecoderReal<float>(json)
    {}
    
    void metadata(Meta* m) { JSONUIDecoderReal<float>::metadata(m); }
    void metadata(MetaGlue* glue) { JSONUIDecoderReal<float>::metadata(glue); }
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    int getSampleRate(char* memory_block)  { return JSONUIDecoderReal<float>::getSampleRate(memory_block); }
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        JSONUIDecoderReal<float>::setReflectZoneFun(index, fun);
    }
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        JSONUIDecoderReal<float>::setModifyZoneFun(index, fun);
    }
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        JSONUIDecoderReal<float>::resetUserInterface(memory_block, defaultsound);
    }
    void buildUserInterface(UI* ui_interface)
    {
        JSONUIDecoderReal<float>::buildUserInterface(ui_interface);
    }
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        JSONUIDecoderReal<float>::buildUserInterface(ui_interface, memory_block);
    }
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        JSONUIDecoderReal<float>::buildUserInterface(ui_interface, memory_block);
    }
    bool hasCompileOption(const std::string& option) { return JSONUIDecoderReal<float>::hasCompileOption(option); }
};

// Double templated decoder

struct JSONUIDoubleDecoder : public JSONUIDecoderReal<double>, public JSONUITemplatedDecoder
{
    JSONUIDoubleDecoder(const std::string& json):JSONUIDecoderReal<double>(json)
    {}
    
    void metadata(Meta* m) { JSONUIDecoderReal<double>::metadata(m); }
    void metadata(MetaGlue* glue) { JSONUIDecoderReal<double>::metadata(glue); }
    int getDSPSize() { return fDSPSize; }
    std::string getName() { return fName; }
    std::string getLibVersion() { return fVersion; }
    std::string getCompileOptions() { return fCompileOptions; }
    std::vector<std::string> getLibraryList() { return fLibraryList; }
    std::vector<std::string> getIncludePathnames() { return fIncludePathnames; }
    int getNumInputs() { return fNumInputs; }
    int getNumOutputs() { return fNumOutputs; }
    int getSampleRate(char* memory_block) { return JSONUIDecoderReal<double>::getSampleRate(memory_block); }
    void setReflectZoneFun(int index, ReflectFunction fun)
    {
        JSONUIDecoderReal<double>::setReflectZoneFun(index, fun);
    }
    void setModifyZoneFun(int index, ModifyFunction fun)
    {
        JSONUIDecoderReal<double>::setModifyZoneFun(index, fun);
    }
    std::vector<ExtZoneParam*>& getInputControls()
    {
        return fPathInputTable;
    }
    std::vector<ExtZoneParam*>& getOutputControls()
    {
        return fPathOutputTable;
    }
    void resetUserInterface(char* memory_block, Soundfile* defaultsound = nullptr)
    {
        JSONUIDecoderReal<double>::resetUserInterface(memory_block, defaultsound);
    }
    void buildUserInterface(UI* ui_interface)
    {
        JSONUIDecoderReal<double>::buildUserInterface(ui_interface);
    }
    void buildUserInterface(UI* ui_interface, char* memory_block)
    {
        JSONUIDecoderReal<double>::buildUserInterface(ui_interface, memory_block);
    }
    void buildUserInterface(UIGlue* ui_interface, char* memory_block)
    {
        JSONUIDecoderReal<double>::buildUserInterface(ui_interface, memory_block);
    }
    bool hasCompileOption(const std::string& option) { return JSONUIDecoderReal<double>::hasCompileOption(option); }
};

// FAUSTFLOAT templated decoder

struct JSONUIDecoder : public JSONUIDecoderReal<FAUSTFLOAT>
{
    JSONUIDecoder(const std::string& json):JSONUIDecoderReal<FAUSTFLOAT>(json)
    {}
};

// Generic factory

static JSONUITemplatedDecoder* createJSONUIDecoder(const std::string& json)
{
    JSONUIDecoder decoder(json);
    if (decoder.hasCompileOption("-double")) {
        return new JSONUIDoubleDecoder(json);
    } else {
        return new JSONUIFloatDecoder(json);
    }
}

#endif
/**************************  END  JSONUIDecoder.h **************************/

//----------------------------------------------------------------
//  Proxy dsp definition created from the DSP JSON description
//  This class allows a 'proxy' dsp to control a real dsp 
//  possibly running somewhere else.
//----------------------------------------------------------------

class proxy_dsp : public dsp {

    private:
    
        JSONUIDecoder* fDecoder;
        int fSampleRate;
        
    public:
    
        proxy_dsp():fDecoder(nullptr), fSampleRate(-1)
        {}
    
        proxy_dsp(const std::string& json)
        {
            init(json);
        }
    
        void init(const std::string& json)
        {
            fDecoder = new JSONUIDecoder(json);
            fSampleRate = -1;
        }
          
        proxy_dsp(dsp* dsp)
        {
            JSONUI builder(dsp->getNumInputs(), dsp->getNumOutputs());
            dsp->metadata(&builder);
            dsp->buildUserInterface(&builder);
            fSampleRate = dsp->getSampleRate();
            fDecoder = new JSONUIDecoder(builder.JSON());
        }
      
        virtual ~proxy_dsp()
        {
            delete fDecoder;
        }
       
        virtual int getNumInputs() { return fDecoder->fNumInputs; }
        virtual int getNumOutputs() { return fDecoder->fNumOutputs; }
        
        virtual void buildUserInterface(UI* ui) { fDecoder->buildUserInterface(ui); }
        
        // To possibly implement in a concrete proxy dsp 
        virtual void init(int sample_rate)
        {
            instanceInit(sample_rate);
        }
        virtual void instanceInit(int sample_rate)
        {
            instanceConstants(sample_rate);
            instanceResetUserInterface();
            instanceClear();
        }
        virtual void instanceConstants(int sample_rate) { fSampleRate = sample_rate; }
        virtual void instanceResetUserInterface() { fDecoder->resetUserInterface(); }
        virtual void instanceClear() {}
    
        virtual int getSampleRate() { return fSampleRate; }
    
        virtual proxy_dsp* clone() { return new proxy_dsp(fDecoder->fJSON); }
        virtual void metadata(Meta* m) { fDecoder->metadata(m); }
    
        virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {}
        virtual void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {} 
        
};

#endif
/**************************  END  proxy-dsp.h **************************/
/************************** BEGIN JSONControl.h **************************/
/************************************************************************
 FAUST Architecture File
 Copyright (C) 2019 GRAME, Centre National de Creation Musicale
 ---------------------------------------------------------------------
 This Architecture section is free software; you can redistribute it
 and/or modify it under the terms of the GNU General Public License
 as published by the Free Software Foundation; either version 3 of
 the License, or (at your option) any later version.
 
 This program is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU General Public License for more details.
 
 You should have received a copy of the GNU General Public License
 along with this program; If not, see <http://www.gnu.org/licenses/>.
 
 EXCEPTION : As a special exception, you may create a larger work
 that contains this FAUST architecture section and distribute
 that work under terms of your choice, so long as this FAUST
 architecture section is not modified.
 ************************************************************************/

#ifndef __JSON_CONTROL__
#define __JSON_CONTROL__

#include <string>

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif

struct JSONControl {
    
    virtual std::string getJSON() { return ""; }

    virtual void setParamValue(const std::string& path, FAUSTFLOAT value) {}

    virtual FAUSTFLOAT getParamValue(const std::string& path) { return 0; }
    
    virtual ~JSONControl()
    {}
    
};

#endif
/**************************  END  JSONControl.h **************************/

#define kActiveVoice      0
#define kFreeVoice        -1
#define kReleaseVoice     -2
#define kNoVoice          -3

#define VOICE_STOP_LEVEL  0.0005    // -70 db
#define MIX_BUFFER_SIZE   4096

/**
 * Allows to control zones in a grouped manner.
 */

class GroupUI : public GUI, public PathBuilder
{

    private:

        std::map<std::string, uiGroupItem*> fLabelZoneMap;

        void insertMap(std::string label, FAUSTFLOAT* zone)
        {
            if (!MapUI::endsWith(label, "/gate")
                && !MapUI::endsWith(label, "/freq")
                && !MapUI::endsWith(label, "/key")
                && !MapUI::endsWith(label, "/gain")
                && !MapUI::endsWith(label, "/vel")
                && !MapUI::endsWith(label, "/velocity")) {

                // Groups all controllers except 'freq/key', 'gate', and 'gain/vel|velocity'
                if (fLabelZoneMap.find(label) != fLabelZoneMap.end()) {
                    fLabelZoneMap[label]->addZone(zone);
                } else {
                    fLabelZoneMap[label] = new uiGroupItem(this, zone);
                }
            }
        }

        uiCallbackItem* fPanic;

    public:

        GroupUI(FAUSTFLOAT* zone, uiCallback cb, void* arg)
        {
            fPanic = new uiCallbackItem(this, zone, cb, arg);
        }
    
        virtual ~GroupUI()
        {
            // 'fPanic' is kept and deleted in GUI, so do not delete here
        }

        // -- widget's layouts
        void openTabBox(const char* label)
        {
            pushLabel(label);
        }
        void openHorizontalBox(const char* label)
        {
            pushLabel(label);
        }
        void openVerticalBox(const char* label)
        {
            pushLabel(label);
        }
        void closeBox()
        {
            popLabel();
        }

        // -- active widgets
        void addButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addCheckButton(const char* label, FAUSTFLOAT* zone)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addHorizontalSlider(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }
        void addNumEntry(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT init, FAUSTFLOAT fmin, FAUSTFLOAT fmax, FAUSTFLOAT step)
        {
            insertMap(buildPath(label), zone);
        }

        // -- passive widgets
        void addHorizontalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }
        void addVerticalBargraph(const char* label, FAUSTFLOAT* zone, FAUSTFLOAT fmin, FAUSTFLOAT fmax)
        {
            insertMap(buildPath(label), zone);
        }

};

/**
 * One voice of polyphony.
 */

struct dsp_voice : public MapUI, public decorator_dsp {
    
    typedef std::function<double(int)> TransformFunction;
  
    static double midiToFreq(double note)
    {
        return 440.0 * std::pow(2.0, (note-69.0)/12.0);
    }

    int fNote;                          // Playing note actual pitch
    int fDate;                          // KeyOn date
    int fRelease;                       // Current number of samples used in release mode to detect end of note
    int fMaxRelease;                    // Max of samples used in release mode to detect end of note
    FAUSTFLOAT fLevel;                  // Last audio block level
    std::vector<std::string> fGatePath; // Paths of 'gate' control
    std::vector<std::string> fGainPath; // Paths of 'gain/vel|velocity' control
    std::vector<std::string> fFreqPath; // Paths of 'freq/key' control
    TransformFunction        fKeyFun;   // MIDI key to freq conversion function
    TransformFunction        fVelFun;   // MIDI velocity to gain conversion function
 
    dsp_voice(dsp* dsp):decorator_dsp(dsp)
    {
        // Default versions
        fVelFun = [](int velocity) { return double(velocity)/127.0; };
        fKeyFun = [](int pitch) { return midiToFreq(pitch); };
        dsp->buildUserInterface(this);
        fNote = kFreeVoice;
        fLevel = FAUSTFLOAT(0);
        fDate = 0;
        fRelease = 0;
        fMaxRelease = dsp->getSampleRate()/2; // One 1/2 sec used in release mode to detect end of note
        extractPaths(fGatePath, fFreqPath, fGainPath);
    }
    virtual ~dsp_voice()
    {}

    void extractPaths(std::vector<std::string>& gate, std::vector<std::string>& freq, std::vector<std::string>& gain)
    {
        // Keep gain/vel|velocity, freq/key and gate labels
        for (auto& it : getMap()) {
            std::string path = it.first;
            if (endsWith(path, "/gate")) {
                gate.push_back(path);
            } else if (endsWith(path, "/freq")) {
                fKeyFun = [](int pitch) { return midiToFreq(pitch); };
                freq.push_back(path);
            } else if (endsWith(path, "/key")) {
                fKeyFun = [](int pitch) { return pitch; };
                freq.push_back(path);
            } else if (endsWith(path, "/gain")) {
                fVelFun = [](int velocity) { return double(velocity)/127.0; };
                gain.push_back(path);
            } else if (endsWith(path, "/vel") || endsWith(path, "/velocity")) {
                fVelFun = [](int velocity) { return double(velocity); };
                gain.push_back(path);
            }
        }
    }
   
    // MIDI velocity [0..127]
    void keyOn(int pitch, int velocity)
    {
        keyOn(pitch, fVelFun(velocity));
    }

    // Normalized MIDI velocity [0..1]
    void keyOn(int pitch, double velocity)
    {
        // So that DSP state is always re-initialized
        fDSP->instanceClear();
        
        for (size_t i = 0; i < fFreqPath.size(); i++) {
            setParamValue(fFreqPath[i], fKeyFun(pitch));
        }
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(1));
        }
        for (size_t i = 0; i < fGainPath.size(); i++) {
            setParamValue(fGainPath[i], velocity);
        }
        
        fNote = pitch;
    }

    void keyOff(bool hard = false)
    {
        // No use of velocity for now...
        for (size_t i = 0; i < fGatePath.size(); i++) {
            setParamValue(fGatePath[i], FAUSTFLOAT(0));
        }
        
        if (hard) {
            // Immediately stop voice
            fNote = kFreeVoice;
        } else {
            // Release voice
            fRelease = fMaxRelease;
            fNote = kReleaseVoice;
        }
    }

};

/**
 * A group of voices.
 */

struct dsp_voice_group {

    GroupUI fGroups;

    std::vector<dsp_voice*> fVoiceTable; // Individual voices
    dsp* fVoiceGroup;                    // Voices group to be used for GUI grouped control

    FAUSTFLOAT fPanic;

    bool fVoiceControl;
    bool fGroupControl;

    dsp_voice_group(uiCallback cb, void* arg, bool control, bool group)
        :fGroups(&fPanic, cb, arg),
        fVoiceGroup(0), fPanic(FAUSTFLOAT(0)),
        fVoiceControl(control), fGroupControl(group)
    {}

    virtual ~dsp_voice_group()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            delete fVoiceTable[i];
        }
        delete fVoiceGroup;
    }

    void addVoice(dsp_voice* voice)
    {
        fVoiceTable.push_back(voice);
    }

    void clearVoices()
    {
        fVoiceTable.clear();
    }

    void init()
    {
        // Groups all uiItem for a given path
        fVoiceGroup = new proxy_dsp(fVoiceTable[0]);
        fVoiceGroup->buildUserInterface(&fGroups);
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->buildUserInterface(&fGroups);
        }
    }
    
    void instanceResetUserInterface()
    {
        for (size_t i = 0; i < fVoiceTable.size(); i++) {
            fVoiceTable[i]->instanceResetUserInterface();
        }
    }

    void buildUserInterface(UI* ui_interface)
    {
        if (fVoiceTable.size() > 1) {
            ui_interface->openTabBox("Polyphonic");

            // Grouped voices UI
            ui_interface->openVerticalBox("Voices");
            ui_interface->addButton("Panic", &fPanic);
            fVoiceGroup->buildUserInterface(ui_interface);
            ui_interface->closeBox();

            // If not grouped, also add individual voices UI
            if (!fGroupControl) {
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    char buffer[32];
                    snprintf(buffer, 32, ((fVoiceTable.size() < 8) ? "Voice%ld" : "V%ld"), long(i+1));
                    ui_interface->openHorizontalBox(buffer);
                    fVoiceTable[i]->buildUserInterface(ui_interface);
                    ui_interface->closeBox();
                }
            }

            ui_interface->closeBox();
        } else {
            fVoiceTable[0]->buildUserInterface(ui_interface);
        }
    }

};

/**
 * Base class for MIDI controllable DSP.
 */

#ifdef EMCC
#endif

class dsp_poly : public decorator_dsp, public midi, public JSONControl {

    protected:
    
    #ifdef EMCC
        MapUI fMapUI;
        std::string fJSON;
        midi_handler fMIDIHandler;
        MidiUI fMIDIUI;
    #endif
    
    public:
    
    #ifdef EMCC
        dsp_poly(dsp* dsp):decorator_dsp(dsp), fMIDIUI(&fMIDIHandler)
        {
            JSONUI jsonui(getNumInputs(), getNumOutputs());
            buildUserInterface(&jsonui);
            fJSON = jsonui.JSON(true);
            buildUserInterface(&fMapUI);
            buildUserInterface(&fMIDIUI);
        }
    #else
        dsp_poly(dsp* dsp):decorator_dsp(dsp)
        {}
    #endif
    
        virtual ~dsp_poly() {}
    
        // Reimplemented for EMCC
    #ifdef EMCC
        virtual int getNumInputs() { return decorator_dsp::getNumInputs(); }
        virtual int getNumOutputs() { return decorator_dsp::getNumOutputs(); }
        virtual void buildUserInterface(UI* ui_interface) { decorator_dsp::buildUserInterface(ui_interface); }
        virtual int getSampleRate() { return decorator_dsp::getSampleRate(); }
        virtual void init(int sample_rate) { decorator_dsp::init(sample_rate); }
        virtual void instanceInit(int sample_rate) { decorator_dsp::instanceInit(sample_rate); }
        virtual void instanceConstants(int sample_rate) { decorator_dsp::instanceConstants(sample_rate); }
        virtual void instanceResetUserInterface() { decorator_dsp::instanceResetUserInterface(); }
        virtual void instanceClear() { decorator_dsp::instanceClear(); }
        virtual dsp_poly* clone() { return new dsp_poly(fDSP->clone()); }
        virtual void metadata(Meta* m) { decorator_dsp::metadata(m); }
    
        // Additional API
        std::string getJSON()
        {
            return fJSON;
        }
    
        virtual void setParamValue(const std::string& path, FAUSTFLOAT value)
        {
            fMapUI.setParamValue(path, value);
            GUI::updateAllGuis();
        }
        
        virtual FAUSTFLOAT getParamValue(const std::string& path) { return fMapUI.getParamValue(path); }

        virtual void computeJS(int count, uintptr_t inputs, uintptr_t outputs)
        {
            decorator_dsp::compute(count, reinterpret_cast<FAUSTFLOAT**>(inputs),reinterpret_cast<FAUSTFLOAT**>(outputs));
        }
    #endif
    
        virtual MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return midi::keyOn(channel, pitch, velocity);
        }
        virtual void keyOff(int channel, int pitch, int velocity)
        {
            midi::keyOff(channel, pitch, velocity);
        }
        virtual void keyPress(int channel, int pitch, int press)
        {
            midi::keyPress(channel, pitch, press);
        }
        virtual void chanPress(int channel, int press)
        {
            midi::chanPress(channel, press);
        }
        virtual void ctrlChange(int channel, int ctrl, int value)
        {
            midi::ctrlChange(channel, ctrl, value);
        }
        virtual void ctrlChange14bits(int channel, int ctrl, int value)
        {
            midi::ctrlChange14bits(channel, ctrl, value);
        }
        virtual void pitchWheel(int channel, int wheel)
        {
        #ifdef EMCC
            fMIDIUI.pitchWheel(0., channel, wheel);
            GUI::updateAllGuis();
        #else
            midi::pitchWheel(channel, wheel);
        #endif
        }
        virtual void progChange(int channel, int pgm)
        {
            midi::progChange(channel, pgm);
        }
    
        // Group API
        virtual void setGroup(bool group) {}
        virtual bool getGroup() { return false; }

};

/**
 * Polyphonic DSP: groups a set of DSP to be played together or triggered by MIDI.
 *
 * All voices are preallocated by cloning the single DSP voice given at creation time.
 * Dynamic voice allocation is done in 'getFreeVoice'
 */

class mydsp_poly : public dsp_voice_group, public dsp_poly {

    private:

        FAUSTFLOAT** fMixBuffer;
        FAUSTFLOAT** fOutBuffer;
        int fDate;
  
        FAUSTFLOAT mixCheckVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            FAUSTFLOAT level = 0;
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    level = std::max<FAUSTFLOAT>(level, (FAUSTFLOAT)fabs(mixChannel[frame]));
                    outChannel[frame] += mixChannel[frame];
                }
            }
            return level;
        }
    
        void mixVoice(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                FAUSTFLOAT* mixChannel = mixBuffer[chan];
                FAUSTFLOAT* outChannel = outBuffer[chan];
                for (int frame = 0; frame < count; frame++) {
                    outChannel[frame] += mixChannel[frame];
                }
            }
        }
    
        void copy(int count, FAUSTFLOAT** mixBuffer, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memcpy(outBuffer[chan], mixBuffer[chan], count * sizeof(FAUSTFLOAT));
            }
        }

        void clear(int count, FAUSTFLOAT** outBuffer)
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                memset(outBuffer[chan], 0, count * sizeof(FAUSTFLOAT));
            }
        }
    
        int getPlayingVoice(int pitch)
        {
            int voice_playing = kNoVoice;
            int oldest_date_playing = INT_MAX;
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fNote == pitch) {
                    // Keeps oldest playing voice
                    if (fVoiceTable[i]->fDate < oldest_date_playing) {
                        oldest_date_playing = fVoiceTable[i]->fDate;
                        voice_playing = int(i);
                    }
                }
            }
            
            return voice_playing;
        }
    
        // Always returns a voice
        int getFreeVoice()
        {
            int voice = kNoVoice;
            
            // Looks for the first available voice
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                if (fVoiceTable[i]->fNote == kFreeVoice) {
                    voice = int(i);
                    goto result;
                }
            }

            {
                // Otherwise steal one
                int voice_release = kNoVoice;
                int voice_playing = kNoVoice;
                
                int oldest_date_release = INT_MAX;
                int oldest_date_playing = INT_MAX;

                // Scan all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    if (fVoiceTable[i]->fNote == kReleaseVoice) {
                        // Keeps oldest release voice
                        if (fVoiceTable[i]->fDate < oldest_date_release) {
                            oldest_date_release = fVoiceTable[i]->fDate;
                            voice_release = int(i);
                        }
                    } else {
                        // Otherwise keeps oldest playing voice
                        if (fVoiceTable[i]->fDate < oldest_date_playing) {
                            oldest_date_playing = fVoiceTable[i]->fDate;
                            voice_playing = int(i);
                        }
                    }
                }
            
                // Then decide which one to steal
                if (oldest_date_release != INT_MAX) {
                    std::cout << "Steal release voice : voice_date " << fVoiceTable[voice_release]->fDate;
                    std::cout << " cur_date = " << fDate << " voice = " << voice_release << std::endl;
                    voice = voice_release;
                    goto result;
                } else if (oldest_date_playing != INT_MAX) {
                    std::cout << "Steal playing voice : voice_date " << fVoiceTable[voice_playing]->fDate;
                    std::cout << " cur_date = " << fDate << " voice = " << voice_playing << std::endl;
                    voice = voice_playing;
                    goto result;
                } else {
                    assert(false);
                    return kNoVoice;
                }
            }
            
        result:
            fVoiceTable[voice]->fDate = fDate++;
            fVoiceTable[voice]->fNote = kActiveVoice;
            return voice;
        }

        static void panic(FAUSTFLOAT val, void* arg)
        {
            if (val == FAUSTFLOAT(1)) {
                static_cast<mydsp_poly*>(arg)->allNotesOff(true);
            }
        }

        bool checkPolyphony()
        {
            if (fVoiceTable.size() > 0) {
                return true;
            } else {
                std::cout << "DSP is not polyphonic...\n";
                return false;
            }
        }

    public:
    
        /**
         * Constructor.
         *
         * @param dsp - the dsp to be used for one voice. Beware: mydsp_poly will use and finally delete the pointer.
         * @param nvoices - number of polyphony voices, should be at least 1
         * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
         *                If false all voices are always running.
         * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
         *                a given control on all voices, assuming GUI::updateAllGuis() is called.
         *                If false, all voices can be individually controlled.
         *                setGroup/getGroup methods can be used to set/get the group state.
         *
         */
        mydsp_poly(dsp* dsp,
                   int nvoices,
                   bool control = false,
                   bool group = true)
        : dsp_voice_group(panic, this, control, group), dsp_poly(dsp) // dsp parameter is deallocated by ~dsp_poly
        {
            fDate = 0;

            // Create voices
            assert(nvoices > 0);
            for (int i = 0; i < nvoices; i++) {
                addVoice(new dsp_voice(dsp->clone()));
            }

            // Init audio output buffers
            fMixBuffer = new FAUSTFLOAT*[getNumOutputs()];
            fOutBuffer = new FAUSTFLOAT*[getNumOutputs()];
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                fMixBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
                fOutBuffer[chan] = new FAUSTFLOAT[MIX_BUFFER_SIZE];
            }

            dsp_voice_group::init();
        }

        virtual ~mydsp_poly()
        {
            for (int chan = 0; chan < getNumOutputs(); chan++) {
                delete[] fMixBuffer[chan];
                delete[] fOutBuffer[chan];
            }
            delete[] fMixBuffer;
            delete[] fOutBuffer;
        }

        // DSP API
    
        void buildUserInterface(UI* ui_interface)
        {
            dsp_voice_group::buildUserInterface(ui_interface);
        }

        void init(int sample_rate)
        {
            decorator_dsp::init(sample_rate);
            fVoiceGroup->init(sample_rate);
            fPanic = FAUSTFLOAT(0);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->init(sample_rate);
            }
        }
    
        void instanceInit(int samplingFreq)
        {
            instanceConstants(samplingFreq);
            instanceResetUserInterface();
            instanceClear();
        }

        void instanceConstants(int sample_rate)
        {
            decorator_dsp::instanceConstants(sample_rate);
            fVoiceGroup->instanceConstants(sample_rate);
            
            // Init voices
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceConstants(sample_rate);
            }
        }

        void instanceResetUserInterface()
        {
            decorator_dsp::instanceResetUserInterface();
            fVoiceGroup->instanceResetUserInterface();
            fPanic = FAUSTFLOAT(0);
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceResetUserInterface();
            }
        }

        void instanceClear()
        {
            decorator_dsp::instanceClear();
            fVoiceGroup->instanceClear();
            
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->instanceClear();
            }
        }

        virtual mydsp_poly* clone()
        {
            return new mydsp_poly(fDSP->clone(), int(fVoiceTable.size()), fVoiceControl, fGroupControl);
        }

        void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            assert(count <= MIX_BUFFER_SIZE);

            // First clear the intermediate fOutBuffer
            clear(count, fOutBuffer);

            if (fVoiceControl) {
                // Mix all playing voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    dsp_voice* voice = fVoiceTable[i];
                    if (voice->fNote != kFreeVoice) {
                        voice->compute(count, inputs, fMixBuffer);
                        // Mix it in result
                        voice->fLevel = mixCheckVoice(count, fMixBuffer, fOutBuffer);
                        voice->fRelease -= count;
                        // Check the level to possibly set the voice in kFreeVoice again
                        if ((voice->fNote == kReleaseVoice) && ((voice->fRelease < 0) || (voice->fLevel < VOICE_STOP_LEVEL))) {
                            voice->fNote = kFreeVoice;
                        }
                    }
                }
            } else {
                // Mix all voices
                for (size_t i = 0; i < fVoiceTable.size(); i++) {
                    fVoiceTable[i]->compute(count, inputs, fMixBuffer);
                    mixVoice(count, fMixBuffer, fOutBuffer);
                }
            }
            
            // Finally copy intermediate buffer to outputs
            copy(count, fOutBuffer, outputs);
        }

        void compute(double date_usec, int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs)
        {
            compute(count, inputs, outputs);
        }
    
        // Terminate all active voices, gently or immediately (depending of 'hard' value)
        void allNotesOff(bool hard = false)
        {
            for (size_t i = 0; i < fVoiceTable.size(); i++) {
                fVoiceTable[i]->keyOff(hard);
            }
        }

        // Additional polyphonic API
        MapUI* newVoice()
        {
            int voice = getFreeVoice();
            // So that DSP state is always re-initialized
            fVoiceTable[voice]->instanceClear();
            return fVoiceTable[voice];
        }

        void deleteVoice(MapUI* voice)
        {
            std::vector<dsp_voice*>::iterator it = find(fVoiceTable.begin(), fVoiceTable.end(), reinterpret_cast<dsp_voice*>(voice));
            if (it != fVoiceTable.end()) {
                (*it)->keyOff();
            } else {
                std::cout << "Voice not found\n";
            }
        }
    
        // Group API
        void setGroup(bool group) { fGroupControl = group; }
        bool getGroup() { return fGroupControl; }

        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            if (checkPolyphony()) {
                int voice = getFreeVoice();
                fVoiceTable[voice]->keyOn(pitch, velocity);
                return fVoiceTable[voice];
            } else {
                return 0;
            }
        }

        void keyOff(int channel, int pitch, int velocity = 127)
        {
            if (checkPolyphony()) {
                int voice = getPlayingVoice(pitch);
                if (voice != kNoVoice) {
                    fVoiceTable[voice]->keyOff();
                } else {
                    std::cout << "Playing pitch = " << pitch << " not found\n";
                }
            }
        }

        void ctrlChange(int channel, int ctrl, int value)
        {
            if (ctrl == ALL_NOTES_OFF || ctrl == ALL_SOUND_OFF) {
                allNotesOff();
            }
        }

};

/**
 * Polyphonic DSP with an integrated effect. fPolyDSP will respond to MIDI messages.
 */
class dsp_poly_effect : public dsp_poly {
    
    private:
        
        dsp_poly* fPolyDSP;
        
    public:
        
        dsp_poly_effect(dsp_poly* dsp1, dsp* dsp2)
        :dsp_poly(dsp2), fPolyDSP(dsp1)
        {}
        
        virtual ~dsp_poly_effect()
        {
            // dsp_poly_effect is also a decorator_dsp, which will free fPolyDSP
        }
        
        // MIDI API
        MapUI* keyOn(int channel, int pitch, int velocity)
        {
            return fPolyDSP->keyOn(channel, pitch, velocity);
        }
        void keyOff(int channel, int pitch, int velocity)
        {
            fPolyDSP->keyOff(channel, pitch, velocity);
        }
        void keyPress(int channel, int pitch, int press)
        {
            fPolyDSP->keyPress(channel, pitch, press);
        }
        void chanPress(int channel, int press)
        {
            fPolyDSP->chanPress(channel, press);
        }
        void ctrlChange(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange(channel, ctrl, value);
        }
        void ctrlChange14bits(int channel, int ctrl, int value)
        {
            fPolyDSP->ctrlChange14bits(channel, ctrl, value);
        }
        void pitchWheel(int channel, int wheel)
        {
            fPolyDSP->pitchWheel(channel, wheel);
        }
        void progChange(int channel, int pgm)
        {
            fPolyDSP->progChange(channel, pgm);
        }
        
        // Group API
        void setGroup(bool group)
        {
            fPolyDSP->setGroup(group);
        }
        bool getGroup()
        {
            return fPolyDSP->getGroup();
        }
};

/**
 * Polyphonic DSP factory class. Helper code to support polyphonic DSP source with an integrated effect.
 */

struct dsp_poly_factory : public dsp_factory {
    
    dsp_factory* fProcessFactory;
    dsp_factory* fEffectFactory;
    
    std::string getEffectCode(const std::string& dsp_content)
    {
        std::stringstream effect_code;
        effect_code << "adapt(1,1) = _; adapt(2,2) = _,_; adapt(1,2) = _ <: _,_; adapt(2,1) = _,_ :> _;";
        effect_code << "adaptor(F,G) = adapt(outputs(F),inputs(G)); dsp_code = environment{ " << dsp_content << " };";
        effect_code << "process = adaptor(dsp_code.process, dsp_code.effect) : dsp_code.effect;";
        return effect_code.str();
    }

    dsp_poly_factory(dsp_factory* process_factory = NULL,
                     dsp_factory* effect_factory = NULL):
    fProcessFactory(process_factory)
    ,fEffectFactory(effect_factory)
    {}
    
    virtual ~dsp_poly_factory()
    {}
    
    virtual std::string getName() { return fProcessFactory->getName(); }
    virtual std::string getSHAKey() { return fProcessFactory->getSHAKey(); }
    virtual std::string getDSPCode() { return fProcessFactory->getDSPCode(); }
    virtual std::string getCompileOptions() { return fProcessFactory->getCompileOptions(); }
    virtual std::vector<std::string> getLibraryList() { return fProcessFactory->getLibraryList(); }
    virtual std::vector<std::string> getIncludePathnames() { return fProcessFactory->getIncludePathnames(); }
    
    virtual void setMemoryManager(dsp_memory_manager* manager)
    {
        fProcessFactory->setMemoryManager(manager);
        if (fEffectFactory) {
            fEffectFactory->setMemoryManager(manager);
        }
    }
    virtual dsp_memory_manager* getMemoryManager() { return fProcessFactory->getMemoryManager(); }
    
    /* Create a new polyphonic DSP instance with global effect, to be deleted with C++ 'delete'
     *
     * @param nvoices - number of polyphony voices, should be at least 1
     * @param control - whether voices will be dynamically allocated and controlled (typically by a MIDI controler).
     *                If false all voices are always running.
     * @param group - if true, voices are not individually accessible, a global "Voices" tab will automatically dispatch
     *                a given control on all voices, assuming GUI::updateAllGuis() is called.
     *                If false, all voices can be individually controlled.
     */
    dsp_poly* createPolyDSPInstance(int nvoices, bool control, bool group)
    {
        dsp_poly* dsp_poly = new mydsp_poly(fProcessFactory->createDSPInstance(), nvoices, control, group);
        if (fEffectFactory) {
            // the 'dsp_poly' object has to be controlled with MIDI, so kept separated from new dsp_sequencer(...) object
            return new dsp_poly_effect(dsp_poly, new dsp_sequencer(dsp_poly, fEffectFactory->createDSPInstance()));
        } else {
            return new dsp_poly_effect(dsp_poly, dsp_poly);
        }
    }
    
    /* Create a new DSP instance, to be deleted with C++ 'delete' */
    dsp* createDSPInstance()
    {
        return fProcessFactory->createDSPInstance();
    }
    
};

#endif // __poly_dsp__
/**************************  END  poly-dsp.h **************************/
#endif

// we require macro declarations
#define FAUST_UIMACROS

// but we will ignore most of them
#define FAUST_ADDBUTTON(l,f)
#define FAUST_ADDCHECKBOX(l,f)
#define FAUST_ADDVERTICALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDHORIZONTALSLIDER(l,f,i,a,b,s)
#define FAUST_ADDNUMENTRY(l,f,i,a,b,s)
#define FAUST_ADDVERTICALBARGRAPH(l,f,a,b)
#define FAUST_ADDHORIZONTALBARGRAPH(l,f,a,b)

/******************************************************************************
 *******************************************************************************
 
 VECTOR INTRINSICS
 
 *******************************************************************************
 *******************************************************************************/


/********************END ARCHITECTURE SECTION (part 1/2)****************/

/**************************BEGIN USER SECTION **************************/

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif 

#include <algorithm>
#include <cmath>
#include <math.h>

static float mydsp_faustpower2_f(float value) {
	return (value * value);
}

#ifndef FAUSTCLASS 
#define FAUSTCLASS mydsp
#endif

#ifdef __APPLE__ 
#define exp10f __exp10f
#define exp10 __exp10
#endif

class mydsp : public dsp {
	
 public:
	
	FAUSTFLOAT fHslider0;
	int iRec14[2];
	int fSampleRate;
	float fConst0;
	float fConst1;
	float fConst2;
	FAUSTFLOAT fHslider1;
	float fRec30[2];
	FAUSTFLOAT fHslider2;
	FAUSTFLOAT fHslider3;
	FAUSTFLOAT fButton0;
	float fVec0[2];
	FAUSTFLOAT fHslider4;
	float fRec31[2];
	float fRec27[2];
	float fRec32[2];
	float fRec34[4];
	int IOTA;
	float fRec35[2048];
	float fVec1[2];
	FAUSTFLOAT fHslider5;
	int iRec37[2];
	float fConst3;
	float fRec36[3];
	int iRec38[2];
	float fConst4;
	float fVec2[2];
	float fRec33[2048];
	float fRec24[2];
	float fRec21[2048];
	float fRec23[2];
	float fRec20[4];
	FAUSTFLOAT fButton1;
	float fVec3[2];
	float fVec4[2];
	float fConst5;
	FAUSTFLOAT fHslider6;
	FAUSTFLOAT fHslider7;
	float fConst6;
	float fRec18[3];
	float fRec39[3];
	float fRec40[3];
	float fRec41[3];
	float fRec42[3];
	float fRec43[3];
	float fRec44[3];
	float fRec45[3];
	float fRec46[3];
	float fRec47[3];
	float fRec48[3];
	float fRec49[3];
	float fRec50[3];
	float fRec51[3];
	float fRec52[3];
	float fRec53[3];
	float fRec54[3];
	float fRec55[3];
	float fRec56[3];
	float fRec57[3];
	float fRec58[3];
	float fRec59[3];
	float fRec60[3];
	float fRec61[3];
	float fRec62[3];
	float fRec63[3];
	float fRec64[3];
	float fRec65[3];
	float fRec66[3];
	float fRec67[3];
	float fRec68[3];
	float fRec69[3];
	float fRec70[3];
	float fRec71[3];
	float fRec72[3];
	float fRec73[3];
	float fRec74[3];
	float fRec75[3];
	float fRec76[3];
	float fRec77[3];
	int iRec10[2];
	int iRec6[2];
	float fRec2[2048];
	float fRec0[2];
	
 public:
	
	void metadata(Meta* m) { 
		m->declare("basics.lib/name", "Faust Basic Element Library");
		m->declare("basics.lib/version", "0.1");
		m->declare("copyright", "(c)Romain Michon & John Granzow, CCRMA (Stanford University), GRAME, University of Michigan");
		m->declare("delays.lib/name", "Faust Delay Library");
		m->declare("delays.lib/version", "0.1");
		m->declare("description", "String instrument with a modular body");
		m->declare("envelopes.lib/ar:author", "Yann Orlarey, Stéphane Letz");
		m->declare("envelopes.lib/author", "GRAME");
		m->declare("envelopes.lib/copyright", "GRAME");
		m->declare("envelopes.lib/license", "LGPL with exception");
		m->declare("envelopes.lib/name", "Faust Envelope Library");
		m->declare("envelopes.lib/version", "0.1");
		m->declare("filename", "modularInterpInstrMIDI.dsp");
		m->declare("filters.lib/fir:author", "Julius O. Smith III");
		m->declare("filters.lib/fir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/fir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/iir:author", "Julius O. Smith III");
		m->declare("filters.lib/iir:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/iir:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/lowpass0_highpass1", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass0_highpass1:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:author", "Julius O. Smith III");
		m->declare("filters.lib/lowpass:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/lowpass:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/name", "Faust Filters Library");
		m->declare("filters.lib/tf2:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/tf2s:author", "Julius O. Smith III");
		m->declare("filters.lib/tf2s:copyright", "Copyright (C) 2003-2019 by Julius O. Smith III <jos@ccrma.stanford.edu>");
		m->declare("filters.lib/tf2s:license", "MIT-style STK-4.3 license");
		m->declare("filters.lib/version", "0.2");
		m->declare("license", "MIT");
		m->declare("maths.lib/author", "GRAME");
		m->declare("maths.lib/copyright", "GRAME");
		m->declare("maths.lib/license", "LGPL with exception");
		m->declare("maths.lib/name", "Faust Math Library");
		m->declare("maths.lib/version", "2.3");
		m->declare("name", "modularInterpInstrMIDI");
		m->declare("noises.lib/name", "Faust Noise Generator Library");
		m->declare("noises.lib/version", "0.0");
		m->declare("platform.lib/name", "Generic Platform Library");
		m->declare("platform.lib/version", "0.1");
		m->declare("routes.lib/name", "Faust Signal Routing Library");
		m->declare("routes.lib/version", "0.2");
		m->declare("signals.lib/name", "Faust Signal Routing Library");
		m->declare("signals.lib/version", "0.0");
	}

	virtual int getNumInputs() {
		return 0;
	}
	virtual int getNumOutputs() {
		return 2;
	}
	virtual int getInputRate(int channel) {
		int rate;
		switch ((channel)) {
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	virtual int getOutputRate(int channel) {
		int rate;
		switch ((channel)) {
			case 0: {
				rate = 1;
				break;
			}
			case 1: {
				rate = 1;
				break;
			}
			default: {
				rate = -1;
				break;
			}
		}
		return rate;
	}
	
	static void classInit(int sample_rate) {
	}
	
	virtual void instanceConstants(int sample_rate) {
		fSampleRate = sample_rate;
		fConst0 = std::min<float>(192000.0f, std::max<float>(1.0f, float(fSampleRate)));
		fConst1 = (0.00882352982f * fConst0);
		fConst2 = (0.00147058826f * fConst0);
		fConst3 = (15.707963f / fConst0);
		fConst4 = (0.00200000009f * fConst0);
		fConst5 = (1.0f / fConst0);
		fConst6 = (6.28318548f / fConst0);
	}
	
	virtual void instanceResetUserInterface() {
		fHslider0 = FAUSTFLOAT(0.5f);
		fHslider1 = FAUSTFLOAT(0.80000000000000004f);
		fHslider2 = FAUSTFLOAT(440.0f);
		fHslider3 = FAUSTFLOAT(0.0f);
		fButton0 = FAUSTFLOAT(0.0f);
		fHslider4 = FAUSTFLOAT(0.0f);
		fHslider5 = FAUSTFLOAT(0.80000000000000004f);
		fButton1 = FAUSTFLOAT(0.0f);
		fHslider6 = FAUSTFLOAT(0.0f);
		fHslider7 = FAUSTFLOAT(0.0f);
	}
	
	virtual void instanceClear() {
		for (int l0 = 0; (l0 < 2); l0 = (l0 + 1)) {
			iRec14[l0] = 0;
		}
		for (int l1 = 0; (l1 < 2); l1 = (l1 + 1)) {
			fRec30[l1] = 0.0f;
		}
		for (int l2 = 0; (l2 < 2); l2 = (l2 + 1)) {
			fVec0[l2] = 0.0f;
		}
		for (int l3 = 0; (l3 < 2); l3 = (l3 + 1)) {
			fRec31[l3] = 0.0f;
		}
		for (int l4 = 0; (l4 < 2); l4 = (l4 + 1)) {
			fRec27[l4] = 0.0f;
		}
		for (int l5 = 0; (l5 < 2); l5 = (l5 + 1)) {
			fRec32[l5] = 0.0f;
		}
		for (int l6 = 0; (l6 < 4); l6 = (l6 + 1)) {
			fRec34[l6] = 0.0f;
		}
		IOTA = 0;
		for (int l7 = 0; (l7 < 2048); l7 = (l7 + 1)) {
			fRec35[l7] = 0.0f;
		}
		for (int l8 = 0; (l8 < 2); l8 = (l8 + 1)) {
			fVec1[l8] = 0.0f;
		}
		for (int l9 = 0; (l9 < 2); l9 = (l9 + 1)) {
			iRec37[l9] = 0;
		}
		for (int l10 = 0; (l10 < 3); l10 = (l10 + 1)) {
			fRec36[l10] = 0.0f;
		}
		for (int l11 = 0; (l11 < 2); l11 = (l11 + 1)) {
			iRec38[l11] = 0;
		}
		for (int l12 = 0; (l12 < 2); l12 = (l12 + 1)) {
			fVec2[l12] = 0.0f;
		}
		for (int l13 = 0; (l13 < 2048); l13 = (l13 + 1)) {
			fRec33[l13] = 0.0f;
		}
		for (int l14 = 0; (l14 < 2); l14 = (l14 + 1)) {
			fRec24[l14] = 0.0f;
		}
		for (int l15 = 0; (l15 < 2048); l15 = (l15 + 1)) {
			fRec21[l15] = 0.0f;
		}
		for (int l16 = 0; (l16 < 2); l16 = (l16 + 1)) {
			fRec23[l16] = 0.0f;
		}
		for (int l17 = 0; (l17 < 4); l17 = (l17 + 1)) {
			fRec20[l17] = 0.0f;
		}
		for (int l18 = 0; (l18 < 2); l18 = (l18 + 1)) {
			fVec3[l18] = 0.0f;
		}
		for (int l19 = 0; (l19 < 2); l19 = (l19 + 1)) {
			fVec4[l19] = 0.0f;
		}
		for (int l20 = 0; (l20 < 3); l20 = (l20 + 1)) {
			fRec18[l20] = 0.0f;
		}
		for (int l21 = 0; (l21 < 3); l21 = (l21 + 1)) {
			fRec39[l21] = 0.0f;
		}
		for (int l22 = 0; (l22 < 3); l22 = (l22 + 1)) {
			fRec40[l22] = 0.0f;
		}
		for (int l23 = 0; (l23 < 3); l23 = (l23 + 1)) {
			fRec41[l23] = 0.0f;
		}
		for (int l24 = 0; (l24 < 3); l24 = (l24 + 1)) {
			fRec42[l24] = 0.0f;
		}
		for (int l25 = 0; (l25 < 3); l25 = (l25 + 1)) {
			fRec43[l25] = 0.0f;
		}
		for (int l26 = 0; (l26 < 3); l26 = (l26 + 1)) {
			fRec44[l26] = 0.0f;
		}
		for (int l27 = 0; (l27 < 3); l27 = (l27 + 1)) {
			fRec45[l27] = 0.0f;
		}
		for (int l28 = 0; (l28 < 3); l28 = (l28 + 1)) {
			fRec46[l28] = 0.0f;
		}
		for (int l29 = 0; (l29 < 3); l29 = (l29 + 1)) {
			fRec47[l29] = 0.0f;
		}
		for (int l30 = 0; (l30 < 3); l30 = (l30 + 1)) {
			fRec48[l30] = 0.0f;
		}
		for (int l31 = 0; (l31 < 3); l31 = (l31 + 1)) {
			fRec49[l31] = 0.0f;
		}
		for (int l32 = 0; (l32 < 3); l32 = (l32 + 1)) {
			fRec50[l32] = 0.0f;
		}
		for (int l33 = 0; (l33 < 3); l33 = (l33 + 1)) {
			fRec51[l33] = 0.0f;
		}
		for (int l34 = 0; (l34 < 3); l34 = (l34 + 1)) {
			fRec52[l34] = 0.0f;
		}
		for (int l35 = 0; (l35 < 3); l35 = (l35 + 1)) {
			fRec53[l35] = 0.0f;
		}
		for (int l36 = 0; (l36 < 3); l36 = (l36 + 1)) {
			fRec54[l36] = 0.0f;
		}
		for (int l37 = 0; (l37 < 3); l37 = (l37 + 1)) {
			fRec55[l37] = 0.0f;
		}
		for (int l38 = 0; (l38 < 3); l38 = (l38 + 1)) {
			fRec56[l38] = 0.0f;
		}
		for (int l39 = 0; (l39 < 3); l39 = (l39 + 1)) {
			fRec57[l39] = 0.0f;
		}
		for (int l40 = 0; (l40 < 3); l40 = (l40 + 1)) {
			fRec58[l40] = 0.0f;
		}
		for (int l41 = 0; (l41 < 3); l41 = (l41 + 1)) {
			fRec59[l41] = 0.0f;
		}
		for (int l42 = 0; (l42 < 3); l42 = (l42 + 1)) {
			fRec60[l42] = 0.0f;
		}
		for (int l43 = 0; (l43 < 3); l43 = (l43 + 1)) {
			fRec61[l43] = 0.0f;
		}
		for (int l44 = 0; (l44 < 3); l44 = (l44 + 1)) {
			fRec62[l44] = 0.0f;
		}
		for (int l45 = 0; (l45 < 3); l45 = (l45 + 1)) {
			fRec63[l45] = 0.0f;
		}
		for (int l46 = 0; (l46 < 3); l46 = (l46 + 1)) {
			fRec64[l46] = 0.0f;
		}
		for (int l47 = 0; (l47 < 3); l47 = (l47 + 1)) {
			fRec65[l47] = 0.0f;
		}
		for (int l48 = 0; (l48 < 3); l48 = (l48 + 1)) {
			fRec66[l48] = 0.0f;
		}
		for (int l49 = 0; (l49 < 3); l49 = (l49 + 1)) {
			fRec67[l49] = 0.0f;
		}
		for (int l50 = 0; (l50 < 3); l50 = (l50 + 1)) {
			fRec68[l50] = 0.0f;
		}
		for (int l51 = 0; (l51 < 3); l51 = (l51 + 1)) {
			fRec69[l51] = 0.0f;
		}
		for (int l52 = 0; (l52 < 3); l52 = (l52 + 1)) {
			fRec70[l52] = 0.0f;
		}
		for (int l53 = 0; (l53 < 3); l53 = (l53 + 1)) {
			fRec71[l53] = 0.0f;
		}
		for (int l54 = 0; (l54 < 3); l54 = (l54 + 1)) {
			fRec72[l54] = 0.0f;
		}
		for (int l55 = 0; (l55 < 3); l55 = (l55 + 1)) {
			fRec73[l55] = 0.0f;
		}
		for (int l56 = 0; (l56 < 3); l56 = (l56 + 1)) {
			fRec74[l56] = 0.0f;
		}
		for (int l57 = 0; (l57 < 3); l57 = (l57 + 1)) {
			fRec75[l57] = 0.0f;
		}
		for (int l58 = 0; (l58 < 3); l58 = (l58 + 1)) {
			fRec76[l58] = 0.0f;
		}
		for (int l59 = 0; (l59 < 3); l59 = (l59 + 1)) {
			fRec77[l59] = 0.0f;
		}
		for (int l60 = 0; (l60 < 2); l60 = (l60 + 1)) {
			iRec10[l60] = 0;
		}
		for (int l61 = 0; (l61 < 2); l61 = (l61 + 1)) {
			iRec6[l61] = 0;
		}
		for (int l62 = 0; (l62 < 2048); l62 = (l62 + 1)) {
			fRec2[l62] = 0.0f;
		}
		for (int l63 = 0; (l63 < 2); l63 = (l63 + 1)) {
			fRec0[l63] = 0.0f;
		}
	}
	
	virtual void init(int sample_rate) {
		classInit(sample_rate);
		instanceInit(sample_rate);
	}
	virtual void instanceInit(int sample_rate) {
		instanceConstants(sample_rate);
		instanceResetUserInterface();
		instanceClear();
	}
	
	virtual mydsp* clone() {
		return new mydsp();
	}
	
	virtual int getSampleRate() {
		return fSampleRate;
	}
	
	virtual void buildUserInterface(UI* ui_interface) {
		ui_interface->openVerticalBox("modularInterpInstr");
		ui_interface->declare(0, "0", "");
		ui_interface->openHorizontalBox("midi");
		ui_interface->declare(&fHslider2, "0", "");
		ui_interface->declare(&fHslider2, "style", "knob");
		ui_interface->addHorizontalSlider("freq", &fHslider2, 440.0f, 50.0f, 1000.0f, 0.00999999978f);
		ui_interface->declare(&fHslider4, "1", "");
		ui_interface->declare(&fHslider4, "hidden", "1");
		ui_interface->declare(&fHslider4, "midi", "pitchwheel");
		ui_interface->declare(&fHslider4, "style", "knob");
		ui_interface->addHorizontalSlider("bend", &fHslider4, 0.0f, -2.0f, 2.0f, 0.00999999978f);
		ui_interface->declare(&fHslider5, "2", "");
		ui_interface->declare(&fHslider5, "style", "knob");
		ui_interface->addHorizontalSlider("gain", &fHslider5, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider3, "3", "");
		ui_interface->declare(&fHslider3, "hidden", "1");
		ui_interface->declare(&fHslider3, "midi", "ctrl 64");
		ui_interface->declare(&fHslider3, "style", "knob");
		ui_interface->addHorizontalSlider("sustain", &fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
		ui_interface->closeBox();
		ui_interface->declare(0, "1", "");
		ui_interface->openHorizontalBox("body");
		ui_interface->declare(&fHslider7, "0", "");
		ui_interface->declare(&fHslider7, "style", "knob");
		ui_interface->addHorizontalSlider("shape", &fHslider7, 0.0f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider6, "1", "");
		ui_interface->declare(&fHslider6, "style", "knob");
		ui_interface->addHorizontalSlider("scale", &fHslider6, 0.0f, 0.0f, 1.0f, 0.0109999999f);
		ui_interface->declare(&fButton1, "2", "");
		ui_interface->addButton("tapBody", &fButton1);
		ui_interface->closeBox();
		ui_interface->declare(&fHslider1, "2", "");
		ui_interface->declare(&fHslider1, "midi", "ctrl 1");
		ui_interface->addHorizontalSlider("pluckPosition", &fHslider1, 0.800000012f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fHslider0, "3", "");
		ui_interface->addHorizontalSlider("outGain", &fHslider0, 0.5f, 0.0f, 1.0f, 0.00999999978f);
		ui_interface->declare(&fButton0, "4", "");
		ui_interface->addButton("gate", &fButton0);
		ui_interface->closeBox();
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* output0 = outputs[0];
		FAUSTFLOAT* output1 = outputs[1];
		float fSlow0 = (0.5f * float(fHslider0));
		float fSlow1 = (0.00100000005f * float(fHslider1));
		float fSlow2 = float(fHslider2);
		float fSlow3 = (340.0f / fSlow2);
		float fSlow4 = std::min<float>(1.0f, (float(fHslider3) + float(fButton0)));
		int iSlow5 = (fSlow4 == 0.0f);
		float fSlow6 = std::pow(2.0f, (0.0833333358f * float(fHslider4)));
		float fSlow7 = float(fHslider5);
		float fSlow8 = (fConst3 * fSlow2);
		float fSlow9 = (0.000500000024f * fSlow2);
		float fSlow10 = float(fButton1);
		float fSlow11 = (2.0f * float(fHslider6));
		int iSlow12 = (fSlow11 < 1.0f);
		float fSlow13 = float(fHslider7);
		float fSlow14 = (2.0f * fSlow13);
		int iSlow15 = (fSlow14 < 1.0f);
		float fSlow16 = (fSlow14 + -1.0f);
		float fSlow17 = (iSlow15 ? (0.236061007f - (0.0507819988f * fSlow13)) : (0.210669994f - (0.0170159992f * fSlow16)));
		float fSlow18 = (iSlow12 ? (iSlow15 ? ((0.0689079985f * fSlow13) + 0.102256f) : ((0.0633310005f * fSlow16) + 0.136710003f)) : fSlow17);
		float fSlow19 = (iSlow12 ? fSlow11 : (fSlow11 + -1.0f));
		float fSlow20 = std::pow(0.00100000005f, (fConst5 / (fSlow18 + (((iSlow12 ? fSlow17 : (iSlow15 ? (0.417113006f - (0.444103986f * fSlow13)) : ((0.0884829983f * fSlow16) + 0.195060998f))) - fSlow18) * fSlow19))));
		float fSlow21 = (0.0f - (2.0f * fSlow20));
		float fSlow22 = (iSlow15 ? ((20.5363007f * fSlow13) + 306.243378f) : ((64.3991241f * fSlow16) + 316.511536f));
		float fSlow23 = (iSlow12 ? (iSlow15 ? ((131.14035f * fSlow13) + 375.008209f) : ((70.5411301f * fSlow16) + 440.578369f)) : fSlow22);
		float fSlow24 = std::cos((fConst6 * (fSlow23 + (fSlow19 * ((iSlow12 ? fSlow22 : (iSlow15 ? ((193.162384f * fSlow13) + 222.231628f) : (318.812836f - (32.678421f * fSlow16)))) - fSlow23)))));
		float fSlow25 = mydsp_faustpower2_f(fSlow20);
		float fSlow26 = (iSlow15 ? (1.0f - (0.000717999996f * fSlow13)) : ((0.000358999998f * fSlow16) + 0.999641001f));
		float fSlow27 = (iSlow12 ? (iSlow15 ? ((0.0178599991f * fSlow13) + 0.991069973f) : 1.0f) : fSlow26);
		float fSlow28 = (fSlow27 + (fSlow19 * ((iSlow12 ? fSlow26 : (iSlow15 ? ((0.837545991f * fSlow13) + 0.581227005f) : 1.0f)) - fSlow27)));
		float fSlow29 = (iSlow15 ? (0.179001004f - (0.233344004f * fSlow13)) : ((0.013727f * fSlow16) + 0.0623290017f));
		float fSlow30 = (iSlow12 ? (iSlow15 ? (0.0880689994f - (0.0348259993f * fSlow13)) : (0.0706560016f - (0.0404569991f * fSlow16))) : fSlow29);
		float fSlow31 = std::pow(0.00100000005f, (fConst5 / (fSlow30 + (fSlow19 * ((iSlow12 ? fSlow29 : (iSlow15 ? ((0.043536f * fSlow13) + 0.247979999f) : (0.269748002f - (0.193024993f * fSlow16)))) - fSlow30)))));
		float fSlow32 = (0.0f - (2.0f * fSlow31));
		float fSlow33 = (iSlow15 ? ((244.433777f * fSlow13) + 426.381561f) : ((67.264389f * fSlow16) + 548.59845f));
		float fSlow34 = (iSlow12 ? (iSlow15 ? ((219.346878f * fSlow13) + 527.945557f) : ((223.278427f * fSlow16) + 637.619019f)) : fSlow33);
		float fSlow35 = std::cos((fConst6 * (fSlow34 + (fSlow19 * ((iSlow12 ? fSlow33 : (iSlow15 ? ((418.606201f * fSlow13) + 336.343597f) : (545.646729f - (69.2622604f * fSlow16)))) - fSlow34)))));
		float fSlow36 = mydsp_faustpower2_f(fSlow31);
		float fSlow37 = (iSlow15 ? ((1.01117802f * fSlow13) + 0.292591989f) : (0.798180997f - (0.360686004f * fSlow16)));
		float fSlow38 = (iSlow12 ? (iSlow15 ? (1.0f - (1.40560603f * fSlow13)) : ((0.389373004f * fSlow16) + 0.297197014f)) : fSlow37);
		float fSlow39 = (fSlow38 + (fSlow19 * ((iSlow12 ? fSlow37 : (iSlow15 ? (1.0f - (1.22786999f * fSlow13)) : ((0.223646f * fSlow16) + 0.386065006f))) - fSlow38)));
		float fSlow40 = (iSlow15 ? ((0.0260600001f * fSlow13) + 0.0844400004f) : ((0.100047f * fSlow16) + 0.0974700004f));
		float fSlow41 = (iSlow12 ? (iSlow15 ? ((0.0470639989f * fSlow13) + 0.0264330003f) : ((0.000890000025f * fSlow16) + 0.0499650016f)) : fSlow40);
		float fSlow42 = std::pow(0.00100000005f, (fConst5 / (fSlow41 + (fSlow19 * ((iSlow12 ? fSlow40 : (iSlow15 ? ((0.00919600017f * fSlow13) + 0.103790998f) : ((0.179033995f * fSlow16) + 0.108388998f))) - fSlow41)))));
		float fSlow43 = (0.0f - (2.0f * fSlow42));
		float fSlow44 = (iSlow15 ? ((318.602051f * fSlow13) + 523.626587f) : ((250.928055f * fSlow16) + 682.927612f));
		float fSlow45 = (iSlow12 ? (iSlow15 ? ((106.360153f * fSlow13) + 775.002563f) : ((149.493057f * fSlow16) + 828.182617f)) : fSlow44);
		float fSlow46 = std::cos((fConst6 * (fSlow45 + (fSlow19 * ((iSlow12 ? fSlow44 : (iSlow15 ? ((344.125305f * fSlow13) + 555.041077f) : (727.103699f - (124.231133f * fSlow16)))) - fSlow45)))));
		float fSlow47 = mydsp_faustpower2_f(fSlow42);
		float fSlow48 = (iSlow15 ? (0.554709971f - (0.709259987f * fSlow13)) : (0.200080007f - (0.089482002f * fSlow16)));
		float fSlow49 = (iSlow12 ? (iSlow15 ? ((0.398301989f * fSlow13) + 0.515945971f) : (0.71509701f - (0.352481008f * fSlow16))) : fSlow48);
		float fSlow50 = (fSlow49 + (fSlow19 * ((iSlow12 ? fSlow48 : (iSlow15 ? ((0.261114001f * fSlow13) + 0.167365998f) : (0.297922999f - (0.0755480006f * fSlow16)))) - fSlow49)));
		float fSlow51 = (iSlow15 ? (0.165197f - (0.0567900017f * fSlow13)) : (0.136802003f - (0.117326997f * fSlow16)));
		float fSlow52 = (iSlow12 ? (iSlow15 ? (0.131998003f - (0.195787996f * fSlow13)) : (0.0341040008f - (0.0139690004f * fSlow16))) : fSlow51);
		float fSlow53 = std::pow(0.00100000005f, (fConst5 / (fSlow52 + (fSlow19 * ((iSlow12 ? fSlow51 : (iSlow15 ? ((0.00264599989f * fSlow13) + 0.131234005f) : (0.132557005f - (0.0741659999f * fSlow16)))) - fSlow52)))));
		float fSlow54 = (0.0f - (2.0f * fSlow53));
		float fSlow55 = (iSlow15 ? ((252.549133f * fSlow13) + 637.81366f) : ((364.68161f * fSlow16) + 764.088196f));
		float fSlow56 = (iSlow12 ? (iSlow15 ? (981.58429f - (6.60999012f * fSlow13)) : ((267.175415f * fSlow16) + 978.279297f)) : fSlow55);
		float fSlow57 = std::cos((fConst6 * (fSlow56 + (fSlow19 * ((iSlow12 ? fSlow55 : (iSlow15 ? ((82.3731384f * fSlow13) + 772.219666f) : ((18.4171124f * fSlow16) + 813.40625f))) - fSlow56)))));
		float fSlow58 = mydsp_faustpower2_f(fSlow53);
		float fSlow59 = (iSlow15 ? (0.359595001f - (0.158243999f * fSlow13)) : (0.280472994f - (0.254615009f * fSlow16)));
		float fSlow60 = (iSlow12 ? (iSlow15 ? (0.549911022f - (0.742200017f * fSlow13)) : (0.178810999f - (0.000125999999f * fSlow16))) : fSlow59);
		float fSlow61 = (fSlow60 + (fSlow19 * ((iSlow12 ? fSlow59 : (iSlow15 ? (0.663183987f - (0.856025994f * fSlow13)) : (0.235171005f - (0.209665999f * fSlow16)))) - fSlow60)));
		float fSlow62 = (iSlow15 ? (0.0838359967f - (0.0120919999f * fSlow13)) : (0.0777899995f - (0.0347030014f * fSlow16)));
		float fSlow63 = (iSlow12 ? (iSlow15 ? (0.0501490012f - (0.052352f * fSlow13)) : (0.0239729993f - (0.00387199991f * fSlow16))) : fSlow62);
		float fSlow64 = std::pow(0.00100000005f, (fConst5 / (fSlow63 + (fSlow19 * ((iSlow12 ? fSlow62 : (iSlow15 ? (0.194764003f - (0.135278001f * fSlow13)) : (0.127124995f - (0.0519529991f * fSlow16)))) - fSlow63)))));
		float fSlow65 = (0.0f - (2.0f * fSlow64));
		float fSlow66 = (iSlow15 ? ((580.437683f * fSlow13) + 855.576416f) : ((85.5582275f * fSlow16) + 1145.79517f));
		float fSlow67 = (iSlow12 ? (iSlow15 ? (1125.20386f - (73.6038437f * fSlow13)) : ((320.421295f * fSlow16) + 1088.40186f)) : fSlow66);
		float fSlow68 = std::cos((fConst6 * (fSlow67 + (fSlow19 * ((iSlow12 ? fSlow66 : (iSlow15 ? ((53.5297089f * fSlow13) + 911.261414f) : (938.026306f - (75.2526855f * fSlow16)))) - fSlow67)))));
		float fSlow69 = mydsp_faustpower2_f(fSlow64);
		float fSlow70 = (iSlow15 ? ((0.00307599991f * fSlow13) + 0.0412230007f) : (0.0427610017f - (0.0319200009f * fSlow16)));
		float fSlow71 = (iSlow12 ? (iSlow15 ? ((0.228167996f * fSlow13) + 0.115278997f) : (0.229362994f - (0.115382001f * fSlow16))) : fSlow70);
		float fSlow72 = (fSlow71 + (fSlow19 * ((iSlow12 ? fSlow70 : (iSlow15 ? ((0.438840002f * fSlow13) + 0.127173007f) : (0.346592993f - (0.320484996f * fSlow16)))) - fSlow71)));
		float fSlow73 = (iSlow15 ? (0.0555430017f - (0.0593319982f * fSlow13)) : ((0.0379519984f * fSlow16) + 0.0258770008f));
		float fSlow74 = (iSlow12 ? (iSlow15 ? (0.0528969988f - (0.0398139991f * fSlow13)) : (0.0329900011f - (0.0060800002f * fSlow16))) : fSlow73);
		float fSlow75 = std::pow(0.00100000005f, (fConst5 / (fSlow74 + (fSlow19 * ((iSlow12 ? fSlow73 : (iSlow15 ? (0.130568996f - (0.0336199999f * fSlow13)) : ((0.00703499978f * fSlow16) + 0.113759004f))) - fSlow74)))));
		float fSlow76 = (0.0f - (2.0f * fSlow75));
		float fSlow77 = (iSlow15 ? ((575.737061f * fSlow13) + 992.200439f) : ((124.879097f * fSlow16) + 1280.06897f));
		float fSlow78 = (iSlow12 ? (iSlow15 ? ((67.2286072f * fSlow13) + 1287.70142f) : ((283.163177f * fSlow16) + 1321.31567f)) : fSlow77);
		float fSlow79 = std::cos((fConst6 * (fSlow78 + (fSlow19 * ((iSlow12 ? fSlow77 : (iSlow15 ? (1096.77429f - (58.6029396f * fSlow13)) : (1067.47278f - (42.4874916f * fSlow16)))) - fSlow78)))));
		float fSlow80 = mydsp_faustpower2_f(fSlow75);
		float fSlow81 = (iSlow15 ? (0.283248991f - (0.406587988f * fSlow13)) : (0.0799549967f - (0.0575550012f * fSlow16)));
		float fSlow82 = (iSlow12 ? (iSlow15 ? ((0.0518359989f * fSlow13) + 0.157812998f) : (0.183731005f - (0.0250039995f * fSlow16))) : fSlow81);
		float fSlow83 = (fSlow82 + (fSlow19 * ((iSlow12 ? fSlow81 : (iSlow15 ? ((0.155338004f * fSlow13) + 0.141424f) : (0.219092995f - (0.192252994f * fSlow16)))) - fSlow82)));
		float fSlow84 = (iSlow15 ? (0.0670289993f - (0.0247939993f * fSlow13)) : ((0.0196759999f * fSlow16) + 0.0546320006f));
		float fSlow85 = (iSlow12 ? (iSlow15 ? (0.0665310025f - (0.0338519998f * fSlow13)) : (0.0496050008f - (0.00635599997f * fSlow16))) : fSlow84);
		float fSlow86 = std::pow(0.00100000005f, (fConst5 / (fSlow85 + (fSlow19 * ((iSlow12 ? fSlow84 : (iSlow15 ? ((0.0797979981f * fSlow13) + 0.119615003f) : (0.159513995f - (0.0279740002f * fSlow16)))) - fSlow85)))));
		float fSlow87 = (0.0f - (2.0f * fSlow86));
		float fSlow88 = (iSlow15 ? ((851.399292f * fSlow13) + 1098.8634f) : ((240.078247f * fSlow16) + 1524.56299f));
		float fSlow89 = (iSlow12 ? (iSlow15 ? ((508.284149f * fSlow13) + 1394.79004f) : ((176.925644f * fSlow16) + 1648.93213f)) : fSlow88);
		float fSlow90 = std::cos((fConst6 * (fSlow89 + (fSlow19 * ((iSlow12 ? fSlow88 : (iSlow15 ? ((72.4165039f * fSlow13) + 1203.10278f) : (1239.31104f - (29.3786488f * fSlow16)))) - fSlow89)))));
		float fSlow91 = mydsp_faustpower2_f(fSlow86);
		float fSlow92 = (iSlow15 ? ((0.209232002f * fSlow13) + 0.182056993f) : (0.286673009f - (0.0414320007f * fSlow16)));
		float fSlow93 = (iSlow12 ? (iSlow15 ? (0.463743001f - (0.712116003f * fSlow13)) : (0.107685f - (0.0836180001f * fSlow16))) : fSlow92);
		float fSlow94 = (fSlow93 + (fSlow19 * ((iSlow12 ? fSlow92 : (iSlow15 ? (0.232076004f - (0.362841994f * fSlow13)) : ((0.555112004f * fSlow16) + 0.0506549999f))) - fSlow93)));
		float fSlow95 = (iSlow15 ? ((0.0118760001f * fSlow13) + 0.0545470007f) : (0.0604850017f - (0.000693999988f * fSlow16)));
		float fSlow96 = (iSlow12 ? (iSlow15 ? (0.0606210008f - (0.0676459968f * fSlow13)) : ((0.0140159996f * fSlow16) + 0.0267980006f)) : fSlow95);
		float fSlow97 = std::pow(0.00100000005f, (fConst5 / (fSlow96 + (fSlow19 * ((iSlow12 ? fSlow95 : (iSlow15 ? (0.103862002f - (0.090669997f * fSlow13)) : ((0.0226460006f * fSlow16) + 0.0585270002f))) - fSlow96)))));
		float fSlow98 = (0.0f - (2.0f * fSlow97));
		float fSlow99 = (iSlow15 ? ((900.447693f * fSlow13) + 1226.92273f) : ((418.439911f * fSlow16) + 1677.14661f));
		float fSlow100 = (iSlow12 ? (iSlow15 ? ((480.15625f * fSlow13) + 1577.13867f) : ((143.768311f * fSlow16) + 1817.2168f)) : fSlow99);
		float fSlow101 = std::cos((fConst6 * (fSlow100 + (fSlow19 * ((iSlow12 ? fSlow99 : (iSlow15 ? ((148.796463f * fSlow13) + 1404.01099f) : ((37.1393623f * fSlow16) + 1478.40918f))) - fSlow100)))));
		float fSlow102 = mydsp_faustpower2_f(fSlow97);
		float fSlow103 = (iSlow15 ? ((0.167971998f * fSlow13) + 0.0786660016f) : ((0.0253379997f * fSlow16) + 0.162652001f));
		float fSlow104 = (iSlow12 ? (iSlow15 ? (0.206984997f - (0.172442004f * fSlow13)) : (0.120764002f - (0.0971049964f * fSlow16))) : fSlow103);
		float fSlow105 = (fSlow104 + (fSlow19 * ((iSlow12 ? fSlow103 : (iSlow15 ? ((0.533154011f * fSlow13) + 0.0434539989f) : ((0.0581550002f * fSlow16) + 0.310030997f))) - fSlow104)));
		float fSlow106 = (iSlow15 ? ((0.0308599994f * fSlow13) + 0.0461950004f) : ((0.0209909994f * fSlow16) + 0.0616250001f));
		float fSlow107 = (iSlow12 ? (iSlow15 ? (0.0453150012f - (0.0410760008f * fSlow13)) : ((0.0333510004f * fSlow16) + 0.0247770008f)) : fSlow106);
		float fSlow108 = std::pow(0.00100000005f, (fConst5 / (fSlow107 + (fSlow19 * ((iSlow12 ? fSlow106 : (iSlow15 ? (0.102784999f - (0.0709040016f * fSlow13)) : ((0.0212159995f * fSlow16) + 0.0673329979f))) - fSlow107)))));
		float fSlow109 = (0.0f - (2.0f * fSlow108));
		float fSlow110 = (iSlow15 ? ((1075.90051f * fSlow13) + 1545.95056f) : ((367.319763f * fSlow16) + 2083.90088f));
		float fSlow111 = (iSlow12 ? (iSlow15 ? ((421.722748f * fSlow13) + 1727.82532f) : ((401.517639f * fSlow16) + 1938.68677f)) : fSlow110);
		float fSlow112 = std::cos((fConst6 * (fSlow111 + (fSlow19 * ((iSlow12 ? fSlow110 : (iSlow15 ? ((53.8923645f * fSlow13) + 1540.42041f) : ((210.452988f * fSlow16) + 1567.36658f))) - fSlow111)))));
		float fSlow113 = mydsp_faustpower2_f(fSlow108);
		float fSlow114 = (iSlow15 ? ((0.203593999f * fSlow13) + 0.898203015f) : (1.0f - (0.970350027f * fSlow16)));
		float fSlow115 = (iSlow12 ? (iSlow15 ? (0.131491005f - (0.142110005f * fSlow13)) : ((0.0246769991f * fSlow16) + 0.0604359992f)) : fSlow114);
		float fSlow116 = (fSlow115 + (fSlow19 * ((iSlow12 ? fSlow114 : (iSlow15 ? ((0.0134119997f * fSlow13) + 0.168680996f) : (0.175386995f - (0.0818609968f * fSlow16)))) - fSlow115)));
		float fSlow117 = (iSlow15 ? ((0.0119240005f * fSlow13) + 0.0553900003f) : ((0.0205969997f * fSlow16) + 0.0613519996f));
		float fSlow118 = (iSlow12 ? (iSlow15 ? (0.047412999f - (0.0134840002f * fSlow13)) : ((0.006819f * fSlow16) + 0.0406709984f)) : fSlow117);
		float fSlow119 = std::pow(0.00100000005f, (fConst5 / (fSlow118 + (fSlow19 * ((iSlow12 ? fSlow117 : (iSlow15 ? (0.0799750015f - (0.015958f * fSlow13)) : (0.0719960034f - (0.0370049998f * fSlow16)))) - fSlow118)))));
		float fSlow120 = (0.0f - (2.0f * fSlow119));
		float fSlow121 = (iSlow15 ? ((1162.01501f * fSlow13) + 1704.77625f) : ((280.651825f * fSlow16) + 2285.78369f));
		float fSlow122 = (iSlow12 ? (iSlow15 ? ((626.39447f * fSlow13) + 1860.70032f) : ((420.439972f * fSlow16) + 2173.89746f)) : fSlow121);
		float fSlow123 = std::cos((fConst6 * (fSlow122 + (fSlow19 * ((iSlow12 ? fSlow121 : (iSlow15 ? ((422.542053f * fSlow13) + 1628.94482f) : ((161.590378f * fSlow16) + 1840.21582f))) - fSlow122)))));
		float fSlow124 = mydsp_faustpower2_f(fSlow119);
		float fSlow125 = (iSlow15 ? ((0.409848005f * fSlow13) + 0.105021f) : (0.309944987f - (0.251771003f * fSlow16)));
		float fSlow126 = (iSlow12 ? (iSlow15 ? ((0.518613994f * fSlow13) + 0.244054005f) : (0.503360987f - (0.311136991f * fSlow16))) : fSlow125);
		float fSlow127 = (fSlow126 + (fSlow19 * ((iSlow12 ? fSlow125 : (iSlow15 ? (0.244908005f - (0.128887996f * fSlow13)) : (0.180464f - (0.163808003f * fSlow16)))) - fSlow126)));
		float fSlow128 = (iSlow15 ? ((0.0157079995f * fSlow13) + 0.0527600013f) : (0.060614001f - (0.0177590009f * fSlow16)));
		float fSlow129 = (iSlow12 ? (iSlow15 ? (0.058375001f - (0.038226001f * fSlow13)) : ((0.0119270002f * fSlow16) + 0.0392620005f)) : fSlow128);
		float fSlow130 = std::pow(0.00100000005f, (fConst5 / (fSlow129 + (fSlow19 * ((iSlow12 ? fSlow128 : (iSlow15 ? (0.0688709989f - (0.00374000007f * fSlow13)) : (0.067001f - (0.00676399982f * fSlow16)))) - fSlow129)))));
		float fSlow131 = (0.0f - (2.0f * fSlow130));
		float fSlow132 = (iSlow15 ? ((1226.12732f * fSlow13) + 1839.16309f) : ((329.240387f * fSlow16) + 2452.22681f));
		float fSlow133 = (iSlow12 ? (iSlow15 ? ((1000.31592f * fSlow13) + 1950.80908f) : ((249.074677f * fSlow16) + 2450.96704f)) : fSlow132);
		float fSlow134 = std::cos((fConst6 * (fSlow133 + (fSlow19 * ((iSlow12 ? fSlow132 : (iSlow15 ? ((334.747742f * fSlow13) + 1994.92566f) : ((511.835907f * fSlow16) + 2162.29956f))) - fSlow133)))));
		float fSlow135 = mydsp_faustpower2_f(fSlow130);
		float fSlow136 = (iSlow15 ? ((0.120742001f * fSlow13) + 0.0371560007f) : (0.0975269973f - (0.0904920027f * fSlow16)));
		float fSlow137 = (iSlow12 ? (iSlow15 ? ((0.384299994f * fSlow13) + 0.160114005f) : (0.352263987f - (0.177852005f * fSlow16))) : fSlow136);
		float fSlow138 = (fSlow137 + (fSlow19 * ((iSlow12 ? fSlow136 : (iSlow15 ? (0.193342999f - (0.257254004f * fSlow13)) : ((0.0948840007f * fSlow16) + 0.0647159964f))) - fSlow137)));
		float fSlow139 = (iSlow15 ? (0.0790209994f - (0.0963080004f * fSlow13)) : ((0.00527299987f * fSlow16) + 0.0308669992f));
		float fSlow140 = (iSlow12 ? (iSlow15 ? (0.0590980016f - (0.0477159992f * fSlow13)) : ((0.0338229984f * fSlow16) + 0.0352399983f)) : fSlow139);
		float fSlow141 = std::pow(0.00100000005f, (fConst5 / (fSlow140 + (fSlow19 * ((iSlow12 ? fSlow139 : (iSlow15 ? (0.120829999f - (0.133272007f * fSlow13)) : (0.0541939996f - (0.0400409997f * fSlow16)))) - fSlow140)))));
		float fSlow142 = (0.0f - (2.0f * fSlow141));
		float fSlow143 = (iSlow15 ? ((1590.8833f * fSlow13) + 1983.83252f) : ((167.483261f * fSlow16) + 2779.27417f));
		float fSlow144 = (iSlow12 ? (iSlow15 ? ((1124.28711f * fSlow13) + 2020.16907f) : ((695.453979f * fSlow16) + 2582.31274f)) : fSlow143);
		float fSlow145 = std::cos((fConst6 * (fSlow144 + (fSlow19 * ((iSlow12 ? fSlow143 : (iSlow15 ? ((211.10791f * fSlow13) + 2197.10693f) : ((851.621216f * fSlow16) + 2302.66089f))) - fSlow144)))));
		float fSlow146 = mydsp_faustpower2_f(fSlow141);
		float fSlow147 = (iSlow15 ? (0.128492996f - (0.209058002f * fSlow13)) : (0.0239640009f - (0.0107760001f * fSlow16)));
		float fSlow148 = (iSlow12 ? (iSlow15 ? (0.116273999f - (0.119684003f * fSlow13)) : ((0.103846997f * fSlow16) + 0.0564320013f)) : fSlow147);
		float fSlow149 = (fSlow148 + (fSlow19 * ((iSlow12 ? fSlow147 : (iSlow15 ? (0.147542998f - (0.153643996f * fSlow13)) : (0.0707210004f - (0.0568850003f * fSlow16)))) - fSlow148)));
		float fSlow150 = (iSlow15 ? (0.0737650022f - (0.0686499998f * fSlow13)) : ((0.0291239992f * fSlow16) + 0.0394399986f));
		float fSlow151 = (iSlow12 ? (iSlow15 ? (0.0299500003f - (0.0214719996f * fSlow13)) : ((0.0281300005f * fSlow16) + 0.0192140006f)) : fSlow150);
		float fSlow152 = std::pow(0.00100000005f, (fConst5 / (fSlow151 + (fSlow19 * ((iSlow12 ? fSlow150 : (iSlow15 ? (0.0664009973f - (0.0271659996f * fSlow13)) : ((0.0218909997f * fSlow16) + 0.0528180003f))) - fSlow151)))));
		float fSlow153 = (0.0f - (2.0f * fSlow152));
		float fSlow154 = (iSlow15 ? ((2011.18274f * fSlow13) + 2190.81445f) : ((325.641937f * fSlow16) + 3196.40601f));
		float fSlow155 = (iSlow12 ? (iSlow15 ? ((1124.40845f * fSlow13) + 2185.79883f) : ((640.507507f * fSlow16) + 2748.00317f)) : fSlow154);
		float fSlow156 = std::cos((fConst6 * (fSlow155 + (fSlow19 * ((iSlow12 ? fSlow154 : (iSlow15 ? (2533.35425f - (278.695068f * fSlow13)) : ((935.54895f * fSlow16) + 2394.00684f))) - fSlow155)))));
		float fSlow157 = mydsp_faustpower2_f(fSlow152);
		float fSlow158 = (iSlow15 ? (0.302569002f - (0.356079996f * fSlow13)) : (0.124528997f - (0.114762001f * fSlow16)));
		float fSlow159 = (iSlow12 ? (iSlow15 ? (0.161678001f - (0.237504005f * fSlow13)) : (0.0429259986f - (0.000651000009f * fSlow16))) : fSlow158);
		float fSlow160 = (fSlow159 + (fSlow19 * ((iSlow12 ? fSlow158 : (iSlow15 ? (0.0622139983f - (0.069629997f * fSlow13)) : ((0.016601f * fSlow16) + 0.0273989998f))) - fSlow159)));
		float fSlow161 = (iSlow15 ? (0.0597440004f - (0.0593799986f * fSlow13)) : ((0.0116569996f * fSlow16) + 0.0300539993f));
		float fSlow162 = (iSlow12 ? (iSlow15 ? ((0.0689280033f * fSlow13) + 0.0185369998f) : (0.0530010015f - (0.00355300005f * fSlow16))) : fSlow161);
		float fSlow163 = std::pow(0.00100000005f, (fConst5 / (fSlow162 + (fSlow19 * ((iSlow12 ? fSlow161 : (iSlow15 ? (0.0649639964f - (0.0280579999f * fSlow13)) : ((0.0179580003f * fSlow16) + 0.0509350002f))) - fSlow162)))));
		float fSlow164 = (0.0f - (2.0f * fSlow163));
		float fSlow165 = (iSlow15 ? ((2247.70605f * fSlow13) + 2445.40991f) : ((179.11232f * fSlow16) + 3569.26294f));
		float fSlow166 = (iSlow12 ? (iSlow15 ? ((951.897827f * fSlow13) + 2382.34399f) : ((646.807617f * fSlow16) + 2858.29297f)) : fSlow165);
		float fSlow167 = std::cos((fConst6 * (fSlow166 + (fSlow19 * ((iSlow12 ? fSlow165 : (iSlow15 ? (2672.47021f - (346.146057f * fSlow13)) : ((931.988464f * fSlow16) + 2499.39722f))) - fSlow166)))));
		float fSlow168 = mydsp_faustpower2_f(fSlow163);
		float fSlow169 = (iSlow15 ? ((0.0424659997f * fSlow13) + 0.134081006f) : (0.155313998f - (0.0960299969f * fSlow16)));
		float fSlow170 = (iSlow12 ? (iSlow15 ? ((0.0841339976f * fSlow13) + 0.0488389991f) : (0.0909060016f - (0.0487020016f * fSlow16))) : fSlow169);
		float fSlow171 = (fSlow170 + (fSlow19 * ((iSlow12 ? fSlow169 : (iSlow15 ? (0.112585001f - (0.0712239966f * fSlow13)) : (0.0769729987f - (0.0538699999f * fSlow16)))) - fSlow170)));
		float fSlow172 = (iSlow15 ? (0.0717800036f - (0.067648001f * fSlow13)) : ((0.00584300002f * fSlow16) + 0.0379559994f));
		float fSlow173 = (iSlow12 ? (iSlow15 ? ((0.0436620004f * fSlow13) + 0.0240860004f) : (0.0459170006f - (0.0211970005f * fSlow16))) : fSlow172);
		float fSlow174 = std::pow(0.00100000005f, (fConst5 / (fSlow173 + (fSlow19 * ((iSlow12 ? fSlow172 : (iSlow15 ? ((0.0162020009f * fSlow13) + 0.0372719988f) : (0.0453730002f - (0.012019f * fSlow16)))) - fSlow173)))));
		float fSlow175 = (0.0f - (2.0f * fSlow174));
		float fSlow176 = (iSlow15 ? ((2250.68848f * fSlow13) + 2672.90747f) : ((94.1008072f * fSlow16) + 3798.25171f));
		float fSlow177 = (iSlow12 ? (iSlow15 ? ((771.725525f * fSlow13) + 2587.14087f) : ((1178.45422f * fSlow16) + 2973.00342f)) : fSlow176);
		float fSlow178 = std::cos((fConst6 * (fSlow177 + (fSlow19 * ((iSlow12 ? fSlow176 : (iSlow15 ? (2821.18604f - (193.046799f * fSlow13)) : ((948.994446f * fSlow16) + 2724.6626f))) - fSlow177)))));
		float fSlow179 = mydsp_faustpower2_f(fSlow174);
		float fSlow180 = (iSlow15 ? (0.0901810005f - (0.0291620009f * fSlow13)) : ((0.0852480009f * fSlow16) + 0.0755999982f));
		float fSlow181 = (iSlow12 ? (iSlow15 ? ((0.307123989f * fSlow13) + 0.0713320002f) : (0.224894002f - (0.197675005f * fSlow16))) : fSlow180);
		float fSlow182 = (fSlow181 + (fSlow19 * ((iSlow12 ? fSlow180 : (iSlow15 ? (0.383899003f - (0.595063984f * fSlow13)) : ((0.0216039997f * fSlow16) + 0.0863670036f))) - fSlow181)));
		float fSlow183 = (iSlow15 ? (0.0505100004f - (0.0391240008f * fSlow13)) : (0.030948f - (0.00496000005f * fSlow16)));
		float fSlow184 = (iSlow12 ? (iSlow15 ? ((0.0257600006f * fSlow13) + 0.0329839997f) : (0.0458640009f - (0.0185889993f * fSlow16))) : fSlow183);
		float fSlow185 = std::pow(0.00100000005f, (fConst5 / (fSlow184 + (fSlow19 * ((iSlow12 ? fSlow183 : (iSlow15 ? (0.057999f - (0.0127760004f * fSlow13)) : (0.0516109988f - (0.0195979998f * fSlow16)))) - fSlow184)))));
		float fSlow186 = (0.0f - (2.0f * fSlow185));
		float fSlow187 = (iSlow15 ? ((2577.24292f * fSlow13) + 2782.64282f) : ((269.63208f * fSlow16) + 4071.26416f));
		float fSlow188 = (iSlow12 ? (iSlow15 ? ((885.65979f * fSlow13) + 2792.65283f) : ((1021.82581f * fSlow16) + 3235.48267f)) : fSlow187);
		float fSlow189 = std::cos((fConst6 * (fSlow188 + (fSlow19 * ((iSlow12 ? fSlow187 : (iSlow15 ? (2967.43628f - (181.446457f * fSlow13)) : ((1352.08887f * fSlow16) + 2876.71313f))) - fSlow188)))));
		float fSlow190 = mydsp_faustpower2_f(fSlow185);
		float fSlow191 = (iSlow15 ? ((0.124551997f * fSlow13) + 0.116704002f) : (0.178979993f - (0.171517f * fSlow16)));
		float fSlow192 = (iSlow12 ? (iSlow15 ? ((0.111337997f * fSlow13) + 0.0724819973f) : (0.128151f - (0.0876460001f * fSlow16))) : fSlow191);
		float fSlow193 = (fSlow192 + (fSlow19 * ((iSlow12 ? fSlow191 : (iSlow15 ? (0.0531390011f - (0.0579020008f * fSlow13)) : (0.0241880007f - (0.0104919998f * fSlow16)))) - fSlow192)));
		float fSlow194 = (iSlow15 ? ((0.0196219999f * fSlow13) + 0.0363259986f) : ((0.0113570001f * fSlow16) + 0.0461370014f));
		float fSlow195 = (iSlow12 ? (iSlow15 ? ((0.0238039996f * fSlow13) + 0.0368679985f) : (0.0487699993f - (0.0203629993f * fSlow16))) : fSlow194);
		float fSlow196 = std::pow(0.00100000005f, (fConst5 / (fSlow195 + (fSlow19 * ((iSlow12 ? fSlow194 : (iSlow15 ? ((0.0259499997f * fSlow13) + 0.0384350009f) : (0.0514100008f - (0.0323220007f * fSlow16)))) - fSlow195)))));
		float fSlow197 = (0.0f - (2.0f * fSlow196));
		float fSlow198 = (iSlow15 ? ((2859.89795f * fSlow13) + 2983.85034f) : ((41.0524406f * fSlow16) + 4413.79932f));
		float fSlow199 = (iSlow12 ? (iSlow15 ? ((756.236023f * fSlow13) + 2970.44385f) : ((1076.7572f * fSlow16) + 3348.56201f)) : fSlow198);
		float fSlow200 = std::cos((fConst6 * (fSlow199 + (fSlow19 * ((iSlow12 ? fSlow198 : (iSlow15 ? (3342.1897f - (581.485046f * fSlow13)) : ((1338.39502f * fSlow16) + 3051.44702f))) - fSlow199)))));
		float fSlow201 = mydsp_faustpower2_f(fSlow196);
		float fSlow202 = (iSlow15 ? ((0.0949139968f * fSlow13) + 0.0417109989f) : (0.0891679972f - (0.0723519996f * fSlow16)));
		float fSlow203 = (iSlow12 ? (iSlow15 ? ((0.318883985f * fSlow13) + 0.0976779982f) : (0.257120013f - (0.192254007f * fSlow16))) : fSlow202);
		float fSlow204 = (fSlow203 + (fSlow19 * ((iSlow12 ? fSlow202 : (iSlow15 ? (0.104650997f - (0.00819600001f * fSlow13)) : (0.100552998f - (0.056938f * fSlow16)))) - fSlow203)));
		float fSlow205 = (iSlow15 ? ((0.0183659997f * fSlow13) + 0.0361620001f) : (0.0453450009f - (0.0169920009f * fSlow16)));
		float fSlow206 = (iSlow12 ? (iSlow15 ? ((0.0175519995f * fSlow13) + 0.0322050005f) : (0.0409809984f - (0.0108099999f * fSlow16))) : fSlow205);
		float fSlow207 = std::pow(0.00100000005f, (fConst5 / (fSlow206 + (fSlow19 * ((iSlow12 ? fSlow205 : (iSlow15 ? ((0.0486899987f * fSlow13) + 0.0369269997f) : (0.061271999f - (0.0402799994f * fSlow16)))) - fSlow206)))));
		float fSlow208 = (0.0f - (2.0f * fSlow207));
		float fSlow209 = (iSlow15 ? ((2564.10083f * fSlow13) + 3268.31396f) : ((78.93853f * fSlow16) + 4550.36426f));
		float fSlow210 = (iSlow12 ? (iSlow15 ? ((897.061035f * fSlow13) + 3047.51562f) : ((1030.83264f * fSlow16) + 3496.04614f)) : fSlow209);
		float fSlow211 = std::cos((fConst6 * (fSlow210 + (fSlow19 * ((iSlow12 ? fSlow209 : (iSlow15 ? (3479.72339f - (521.214294f * fSlow13)) : ((1333.62915f * fSlow16) + 3219.11621f))) - fSlow210)))));
		float fSlow212 = mydsp_faustpower2_f(fSlow207);
		float fSlow213 = (iSlow15 ? (0.268207014f - (0.266490012f * fSlow13)) : (0.134962007f - (0.126273006f * fSlow16)));
		float fSlow214 = (iSlow12 ? (iSlow15 ? (0.0834150016f - (0.013998f * fSlow13)) : (0.0764160007f - (0.00734200003f * fSlow16))) : fSlow213);
		float fSlow215 = (fSlow214 + (fSlow19 * ((iSlow12 ? fSlow213 : (iSlow15 ? (0.093520999f - (0.129490003f * fSlow13)) : ((0.0110719996f * fSlow16) + 0.0287759993f))) - fSlow214)));
		float fSlow216 = (iSlow15 ? (0.0392679982f - (0.0278840009f * fSlow13)) : (0.0253260005f - (0.0067400001f * fSlow16)));
		float fSlow217 = (iSlow12 ? (iSlow15 ? (0.0237099994f - (0.00592599995f * fSlow13)) : ((0.00585900014f * fSlow16) + 0.0207470004f)) : fSlow216);
		float fSlow218 = std::pow(0.00100000005f, (fConst5 / (fSlow217 + (fSlow19 * ((iSlow12 ? fSlow216 : (iSlow15 ? ((0.0277479999f * fSlow13) + 0.0369700007f) : (0.0508439988f - (0.0241410006f * fSlow16)))) - fSlow217)))));
		float fSlow219 = (0.0f - (2.0f * fSlow218));
		float fSlow220 = (iSlow15 ? ((3016.71948f * fSlow13) + 3458.03833f) : (4966.39795f - (159.980698f * fSlow16)));
		float fSlow221 = (iSlow12 ? (iSlow15 ? ((747.625061f * fSlow13) + 3332.69531f) : ((923.180298f * fSlow16) + 3706.50781f)) : fSlow220);
		float fSlow222 = std::cos((fConst6 * (fSlow221 + (fSlow19 * ((iSlow12 ? fSlow220 : (iSlow15 ? (3631.70532f - (506.076111f * fSlow13)) : ((1387.48425f * fSlow16) + 3378.66724f))) - fSlow221)))));
		float fSlow223 = mydsp_faustpower2_f(fSlow218);
		float fSlow224 = (iSlow15 ? ((0.0821579993f * fSlow13) + 0.0796509981f) : (0.120729998f - (0.0890860036f * fSlow16)));
		float fSlow225 = (iSlow12 ? (iSlow15 ? ((0.0789740011f * fSlow13) + 0.0574840009f) : (0.0969709978f - (0.0674979985f * fSlow16))) : fSlow224);
		float fSlow226 = (fSlow225 + (fSlow19 * ((iSlow12 ? fSlow224 : (iSlow15 ? (0.0292199999f - (0.00249200012f * fSlow13)) : ((0.0139290001f * fSlow16) + 0.0279740002f))) - fSlow225)));
		float fSlow227 = (iSlow15 ? (0.0317769982f - (0.0125240004f * fSlow13)) : (0.0255149994f - (0.00686400011f * fSlow16)));
		float fSlow228 = (iSlow12 ? (iSlow15 ? (0.0234299991f - (0.00173000002f * fSlow13)) : ((0.00772400014f * fSlow16) + 0.0225649998f)) : fSlow227);
		float fSlow229 = std::pow(0.00100000005f, (fConst5 / (fSlow228 + (fSlow19 * ((iSlow12 ? fSlow227 : (iSlow15 ? (0.0691469982f - (0.0794640034f * fSlow13)) : (0.0294150002f - (0.0113749998f * fSlow16)))) - fSlow228)))));
		float fSlow230 = (0.0f - (2.0f * fSlow229));
		float fSlow231 = (iSlow15 ? ((3131.89868f * fSlow13) + 3590.8501f) : (5156.79932f - (132.253967f * fSlow16)));
		float fSlow232 = (iSlow12 ? (iSlow15 ? ((1035.34338f * fSlow13) + 3416.63623f) : ((884.704407f * fSlow16) + 3934.30786f)) : fSlow231);
		float fSlow233 = std::cos((fConst6 * (fSlow232 + (fSlow19 * ((iSlow12 ? fSlow231 : (iSlow15 ? (3806.88281f - (598.292358f * fSlow13)) : ((1346.61829f * fSlow16) + 3507.73682f))) - fSlow232)))));
		float fSlow234 = mydsp_faustpower2_f(fSlow229);
		float fSlow235 = (iSlow15 ? ((0.00551400008f * fSlow13) + 0.0341279991f) : ((0.00872300006f * fSlow16) + 0.0368850008f));
		float fSlow236 = (iSlow12 ? (iSlow15 ? ((0.0388199985f * fSlow13) + 0.0592590012f) : (0.0786689967f - (0.0456149988f * fSlow16))) : fSlow235);
		float fSlow237 = (fSlow236 + (fSlow19 * ((iSlow12 ? fSlow235 : (iSlow15 ? ((0.0251080003f * fSlow13) + 0.0276459996f) : ((0.00347099989f * fSlow16) + 0.0401999988f))) - fSlow236)));
		float fSlow238 = (iSlow15 ? (0.0379900001f - (0.0309519991f * fSlow13)) : ((0.00286599994f * fSlow16) + 0.0225140005f));
		float fSlow239 = (iSlow12 ? (iSlow15 ? ((0.0311459992f * fSlow13) + 0.0155159999f) : ((0.00968299992f * fSlow16) + 0.0310890004f)) : fSlow238);
		float fSlow240 = std::pow(0.00100000005f, (fConst5 / (fSlow239 + (fSlow19 * ((iSlow12 ? fSlow238 : (iSlow15 ? (0.0360959992f - (0.0282600001f * fSlow13)) : (0.0219659992f - (0.00615100004f * fSlow16)))) - fSlow239)))));
		float fSlow241 = (0.0f - (2.0f * fSlow240));
		float fSlow242 = (iSlow15 ? ((3159.96094f * fSlow13) + 3783.14355f) : ((241.560638f * fSlow16) + 5363.12402f));
		float fSlow243 = (iSlow12 ? (iSlow15 ? ((1809.06396f * fSlow13) + 3513.87646f) : ((1075.21985f * fSlow16) + 4418.4082f)) : fSlow242);
		float fSlow244 = std::cos((fConst6 * (fSlow243 + (fSlow19 * ((iSlow12 ? fSlow242 : (iSlow15 ? (3910.07837f - (444.342133f * fSlow13)) : ((1282.60876f * fSlow16) + 3687.90723f))) - fSlow243)))));
		float fSlow245 = mydsp_faustpower2_f(fSlow240);
		float fSlow246 = (iSlow15 ? (0.296837986f - (0.545635998f * fSlow13)) : (0.0240199994f - (0.00424699998f * fSlow16)));
		float fSlow247 = (iSlow12 ? (iSlow15 ? ((0.0618220009f * fSlow13) + 0.0346620008f) : (0.0655729994f - (0.0102620004f * fSlow16))) : fSlow246);
		float fSlow248 = (fSlow247 + (fSlow19 * ((iSlow12 ? fSlow246 : (iSlow15 ? ((0.0214019995f * fSlow13) + 0.0209790003f) : ((0.0233379994f * fSlow16) + 0.0316799991f))) - fSlow247)));
		float fSlow249 = (iSlow15 ? (0.072567001f - (0.0588500015f * fSlow13)) : (0.0431419984f - (0.021892f * fSlow16)));
		float fSlow250 = (iSlow12 ? (iSlow15 ? ((0.00803000014f * fSlow13) + 0.0227729995f) : (0.026788f - (0.00293199997f * fSlow16))) : fSlow249);
		float fSlow251 = std::pow(0.00100000005f, (fConst5 / (fSlow250 + (fSlow19 * ((iSlow12 ? fSlow249 : (iSlow15 ? (0.0491360016f - (0.0513060018f * fSlow13)) : (0.0234830007f - (0.00681200018f * fSlow16)))) - fSlow250)))));
		float fSlow252 = (0.0f - (2.0f * fSlow251));
		float fSlow253 = (iSlow15 ? ((2976.07202f * fSlow13) + 4123.00244f) : ((60.0741539f * fSlow16) + 5611.03857f));
		float fSlow254 = (iSlow12 ? (iSlow15 ? ((2489.15503f * fSlow13) + 3994.49219f) : ((1084.31396f * fSlow16) + 5239.06982f)) : fSlow253);
		float fSlow255 = std::cos((fConst6 * (fSlow254 + (fSlow19 * ((iSlow12 ? fSlow253 : (iSlow15 ? (4173.7793f - (691.748291f * fSlow13)) : ((1236.29834f * fSlow16) + 3827.90503f))) - fSlow254)))));
		float fSlow256 = mydsp_faustpower2_f(fSlow251);
		float fSlow257 = (iSlow15 ? ((0.101337999f * fSlow13) + 0.0519590005f) : (0.102628f - (0.084082f * fSlow16)));
		float fSlow258 = (iSlow12 ? (iSlow15 ? (0.0644790009f - (0.0141160004f * fSlow13)) : ((0.0162729993f * fSlow16) + 0.0574209988f)) : fSlow257);
		float fSlow259 = (fSlow258 + (fSlow19 * ((iSlow12 ? fSlow257 : (iSlow15 ? (0.0318869986f - (0.0203859992f * fSlow13)) : ((0.0200360008f * fSlow16) + 0.0216940008f))) - fSlow258)));
		float fSlow260 = (iSlow15 ? (0.0458239987f - (0.0543220006f * fSlow13)) : ((0.000554000027f * fSlow16) + 0.0186630003f));
		float fSlow261 = (iSlow12 ? (iSlow15 ? (0.0252650008f - (0.0228739996f * fSlow13)) : ((0.00706099998f * fSlow16) + 0.0138280001f)) : fSlow260);
		float fSlow262 = std::pow(0.00100000005f, (fConst5 / (fSlow261 + (fSlow19 * ((iSlow12 ? fSlow260 : (iSlow15 ? (0.0462680012f - (0.0468039997f * fSlow13)) : ((0.00586599996f * fSlow16) + 0.0228659995f))) - fSlow261)))));
		float fSlow263 = (0.0f - (2.0f * fSlow262));
		float fSlow264 = (iSlow15 ? ((3490.6792f * fSlow13) + 4250.31055f) : ((537.497009f * fSlow16) + 5995.6499f));
		float fSlow265 = (iSlow12 ? (iSlow15 ? ((2599.51294f * fSlow13) + 4128.26172f) : ((1086.49524f * fSlow16) + 5428.01807f)) : fSlow264);
		float fSlow266 = std::cos((fConst6 * (fSlow265 + (fSlow19 * ((iSlow12 ? fSlow264 : (iSlow15 ? (4292.90137f - (506.087036f * fSlow13)) : ((1160.54187f * fSlow16) + 4039.85791f))) - fSlow265)))));
		float fSlow267 = mydsp_faustpower2_f(fSlow262);
		float fSlow268 = (iSlow15 ? (0.124453999f - (0.0783979967f * fSlow13)) : (0.085254997f - (0.0717599988f * fSlow16)));
		float fSlow269 = (iSlow12 ? (iSlow15 ? ((0.0478519984f * fSlow13) + 0.0614520013f) : (0.0853779987f - (0.014037f * fSlow16))) : fSlow268);
		float fSlow270 = (fSlow269 + (fSlow19 * ((iSlow12 ? fSlow268 : (iSlow15 ? (0.0526099987f - (0.0344959982f * fSlow13)) : ((0.0274700001f * fSlow16) + 0.0353620015f))) - fSlow269)));
		float fSlow271 = (iSlow15 ? (0.0265159998f - (0.0229180008f * fSlow13)) : ((0.001269f * fSlow16) + 0.0150570003f));
		float fSlow272 = (iSlow12 ? (iSlow15 ? (0.0288720001f - (0.00990999956f * fSlow13)) : ((0.00894199964f * fSlow16) + 0.0239170007f)) : fSlow271);
		float fSlow273 = std::pow(0.00100000005f, (fConst5 / (fSlow272 + (fSlow19 * ((iSlow12 ? fSlow271 : (iSlow15 ? (0.0294519998f - (0.0120679997f * fSlow13)) : (0.023418f - (0.00548900012f * fSlow16)))) - fSlow272)))));
		float fSlow274 = (0.0f - (2.0f * fSlow273));
		float fSlow275 = (iSlow15 ? ((3508.36353f * fSlow13) + 4408.44238f) : ((589.325562f * fSlow16) + 6162.62402f));
		float fSlow276 = (iSlow12 ? (iSlow15 ? ((3047.81055f * fSlow13) + 4247.82861f) : ((938.245667f * fSlow16) + 5771.73389f)) : fSlow275);
		float fSlow277 = std::cos((fConst6 * (fSlow276 + (fSlow19 * ((iSlow12 ? fSlow275 : (iSlow15 ? (4519.28857f - (621.092041f * fSlow13)) : ((1138.90845f * fSlow16) + 4208.74219f))) - fSlow276)))));
		float fSlow278 = mydsp_faustpower2_f(fSlow273);
		float fSlow279 = (iSlow15 ? (0.0775860026f - (0.0362939984f * fSlow13)) : (0.0594389997f - (0.0409570001f * fSlow16)));
		float fSlow280 = (iSlow12 ? (iSlow15 ? (0.110522002f - (0.0502500013f * fSlow13)) : (0.0853969976f - (0.0170310009f * fSlow16))) : fSlow279);
		float fSlow281 = (fSlow280 + (fSlow19 * ((iSlow12 ? fSlow279 : (iSlow15 ? (0.0450000018f - (0.0263579991f * fSlow13)) : (0.0318210013f - (0.00135699997f * fSlow16)))) - fSlow280)));
		float fSlow282 = (iSlow15 ? ((0.0503199995f * fSlow13) + 0.0276839994f) : (0.0528439991f - (0.0333749987f * fSlow16)));
		float fSlow283 = (iSlow12 ? (iSlow15 ? ((0.00548399985f * fSlow13) + 0.0197429992f) : ((0.00505799986f * fSlow16) + 0.0224849992f)) : fSlow282);
		float fSlow284 = std::pow(0.00100000005f, (fConst5 / (fSlow283 + (fSlow19 * ((iSlow12 ? fSlow282 : (iSlow15 ? ((0.0170120001f * fSlow13) + 0.0250659995f) : (0.0335719995f - (0.0120519996f * fSlow16)))) - fSlow283)))));
		float fSlow285 = (0.0f - (2.0f * fSlow284));
		float fSlow286 = (iSlow15 ? ((4104.11377f * fSlow13) + 4531.91602f) : ((278.80899f * fSlow16) + 6583.97314f));
		float fSlow287 = (iSlow12 ? (iSlow15 ? ((3362.49512f * fSlow13) + 4425.13086f) : ((716.726013f * fSlow16) + 6106.37842f)) : fSlow286);
		float fSlow288 = std::cos((fConst6 * (fSlow287 + (fSlow19 * ((iSlow12 ? fSlow286 : (iSlow15 ? (4631.05371f - (490.803497f * fSlow13)) : ((1074.15564f * fSlow16) + 4385.65186f))) - fSlow287)))));
		float fSlow289 = mydsp_faustpower2_f(fSlow284);
		float fSlow290 = (iSlow15 ? (0.0849149972f - (0.123152003f * fSlow13)) : (0.0233389996f - (0.00320899999f * fSlow16)));
		float fSlow291 = (iSlow12 ? (iSlow15 ? ((0.00961599965f * fSlow13) + 0.0457700007f) : (0.0505779982f - (0.0238429997f * fSlow16))) : fSlow290);
		float fSlow292 = (fSlow291 + (fSlow19 * ((iSlow12 ? fSlow290 : (iSlow15 ? ((0.00836800039f * fSlow13) + 0.023542f) : ((0.000322999986f * fSlow16) + 0.0277260002f))) - fSlow291)));
		float fSlow293 = (iSlow15 ? (0.0342289992f - (0.0355020016f * fSlow13)) : ((0.00427599996f * fSlow16) + 0.0164780002f));
		float fSlow294 = (iSlow12 ? (iSlow15 ? (0.0365649983f - (0.00249200012f * fSlow13)) : (0.0353190005f - (0.00889199972f * fSlow16))) : fSlow293);
		float fSlow295 = std::pow(0.00100000005f, (fConst5 / (fSlow294 + (fSlow19 * ((iSlow12 ? fSlow293 : (iSlow15 ? ((0.0116440002f * fSlow13) + 0.0209420007f) : (0.0267639998f - (0.00214200001f * fSlow16)))) - fSlow294)))));
		float fSlow296 = (0.0f - (2.0f * fSlow295));
		float fSlow297 = (iSlow15 ? ((4328.62793f * fSlow13) + 4865.21191f) : (7029.52588f - (78.2994385f * fSlow16)));
		float fSlow298 = (iSlow12 ? (iSlow15 ? ((3235.23779f * fSlow13) + 4686.89404f) : ((705.235596f * fSlow16) + 6304.5127f)) : fSlow297);
		float fSlow299 = std::cos((fConst6 * (fSlow298 + (fSlow19 * ((iSlow12 ? fSlow297 : (iSlow15 ? (4855.40527f - (561.173401f * fSlow13)) : ((1055.32581f * fSlow16) + 4574.81836f))) - fSlow298)))));
		float fSlow300 = mydsp_faustpower2_f(fSlow295);
		float fSlow301 = (iSlow15 ? (0.126202002f - (0.197518006f * fSlow13)) : (0.0274429992f - (0.0120259998f * fSlow16)));
		float fSlow302 = (iSlow12 ? (iSlow15 ? (0.0533180013f - (0.0135679999f * fSlow13)) : (0.0465340018f - (0.00917499978f * fSlow16))) : fSlow301);
		float fSlow303 = (fSlow302 + (fSlow19 * ((iSlow12 ? fSlow301 : (iSlow15 ? (0.0494260006f - (0.0244139992f * fSlow13)) : (0.0372189991f - (0.0243389998f * fSlow16)))) - fSlow302)));
		float fSlow304 = (iSlow15 ? (0.0408670008f - (0.0297480002f * fSlow13)) : (0.0259930007f - (0.00650600018f * fSlow16)));
		float fSlow305 = (iSlow12 ? (iSlow15 ? (0.0327039994f - (0.0294979997f * fSlow13)) : ((0.0141989999f * fSlow16) + 0.0179549996f)) : fSlow304);
		float fSlow306 = std::pow(0.00100000005f, (fConst5 / (fSlow305 + (fSlow19 * ((iSlow12 ? fSlow304 : (iSlow15 ? (0.040527001f - (0.0463859998f * fSlow13)) : ((0.00537199993f * fSlow16) + 0.0173339993f))) - fSlow305)))));
		float fSlow307 = (0.0f - (2.0f * fSlow306));
		float fSlow308 = (iSlow15 ? ((3918.46655f * fSlow13) + 5248.66064f) : (7207.89404f - (27.0308781f * fSlow16)));
		float fSlow309 = (iSlow12 ? (iSlow15 ? ((4114.18652f * fSlow13) + 4731.1416f) : ((410.681946f * fSlow16) + 6788.23486f)) : fSlow308);
		float fSlow310 = std::cos((fConst6 * (fSlow309 + (fSlow19 * ((iSlow12 ? fSlow308 : (iSlow15 ? (5079.82812f - (671.383423f * fSlow13)) : ((1126.12158f * fSlow16) + 4744.13623f))) - fSlow309)))));
		float fSlow311 = mydsp_faustpower2_f(fSlow306);
		float fSlow312 = (iSlow15 ? ((0.243842006f * fSlow13) + 0.0196969993f) : (0.141617998f - (0.110509001f * fSlow16)));
		float fSlow313 = (iSlow12 ? (iSlow15 ? ((0.324510008f * fSlow13) + 0.0512249991f) : (0.213479996f - (0.187472001f * fSlow16))) : fSlow312);
		float fSlow314 = (fSlow313 + (fSlow19 * ((iSlow12 ? fSlow312 : (iSlow15 ? (0.0290629994f - (0.00551000005f * fSlow13)) : ((0.0208459999f * fSlow16) + 0.0263080001f))) - fSlow313)));
		float fSlow315 = (iSlow15 ? (0.0377999991f - (0.0398400016f * fSlow13)) : ((0.00170999998f * fSlow16) + 0.0178800002f));
		float fSlow316 = (iSlow12 ? (iSlow15 ? (0.0252340008f - (0.0208059996f * fSlow13)) : ((0.00574500021f * fSlow16) + 0.014831f)) : fSlow315);
		float fSlow317 = std::pow(0.00100000005f, (fConst5 / (fSlow316 + (fSlow19 * ((iSlow12 ? fSlow315 : (iSlow15 ? (0.0273739994f - (0.0119599998f * fSlow13)) : ((0.00174400001f * fSlow16) + 0.0213939995f))) - fSlow316)))));
		float fSlow318 = (0.0f - (2.0f * fSlow317));
		float fSlow319 = (iSlow15 ? ((4639.52686f * fSlow13) + 5387.01172f) : ((194.856293f * fSlow16) + 7706.7749f));
		float fSlow320 = (iSlow12 ? (iSlow15 ? ((2702.19263f * fSlow13) + 5553.90479f) : ((2114.24707f * fSlow16) + 6905.00146f)) : fSlow319);
		float fSlow321 = std::cos((fConst6 * (fSlow320 + (fSlow19 * ((iSlow12 ? fSlow319 : (iSlow15 ? (5182.39209f - (630.99646f * fSlow13)) : ((1255.0675f * fSlow16) + 4866.89404f))) - fSlow320)))));
		float fSlow322 = mydsp_faustpower2_f(fSlow317);
		float fSlow323 = (iSlow15 ? ((0.0528200008f * fSlow13) + 0.0176430009f) : (0.0440529995f - (0.0364289992f * fSlow16)));
		float fSlow324 = (iSlow12 ? (iSlow15 ? ((0.110288002f * fSlow13) + 0.0349979997f) : (0.0901419967f - (0.0641840026f * fSlow16))) : fSlow323);
		float fSlow325 = (fSlow324 + (fSlow19 * ((iSlow12 ? fSlow323 : (iSlow15 ? (0.0490619987f - (0.0657960027f * fSlow13)) : ((0.068543002f * fSlow16) + 0.0161639992f))) - fSlow324)));
		float fSlow326 = (iSlow15 ? (0.0268939994f - (0.0257760007f * fSlow13)) : (0.014006f - (0.00265799998f * fSlow16)));
		float fSlow327 = (iSlow12 ? (iSlow15 ? (0.0283829998f - (0.0189619996f * fSlow13)) : ((0.0140880002f * fSlow16) + 0.018902f)) : fSlow326);
		float fSlow328 = std::pow(0.00100000005f, (fConst5 / (fSlow327 + (fSlow19 * ((iSlow12 ? fSlow326 : (iSlow15 ? (0.0309859999f - (0.0100039998f * fSlow13)) : ((0.00133899995f * fSlow16) + 0.0259840004f))) - fSlow327)))));
		float fSlow329 = (0.0f - (2.0f * fSlow328));
		float fSlow330 = (iSlow15 ? ((4126.87646f * fSlow13) + 5780.59375f) : ((230.630157f * fSlow16) + 7844.03223f));
		float fSlow331 = (iSlow12 ? (iSlow15 ? ((2704.97607f * fSlow13) + 5702.20654f) : ((2437.55811f * fSlow16) + 7054.69434f)) : fSlow330);
		float fSlow332 = std::cos((fConst6 * (fSlow331 + (fSlow19 * ((iSlow12 ? fSlow330 : (iSlow15 ? (5328.29199f - (475.518463f * fSlow13)) : ((1153.98975f * fSlow16) + 5090.53271f))) - fSlow331)))));
		float fSlow333 = mydsp_faustpower2_f(fSlow328);
		float fSlow334 = (iSlow15 ? (0.077301003f - (0.106063999f * fSlow13)) : (0.0242689997f - (0.0157430004f * fSlow16)));
		float fSlow335 = (iSlow12 ? (iSlow15 ? ((0.0541879982f * fSlow13) + 0.0515380017f) : (0.0786319971f - (0.0533050001f * fSlow16))) : fSlow334);
		float fSlow336 = (fSlow335 + (fSlow19 * ((iSlow12 ? fSlow334 : (iSlow15 ? ((0.0156820007f * fSlow13) + 0.0150969997f) : ((0.0275940001f * fSlow16) + 0.022938f))) - fSlow335)));
		float fSlow337 = (iSlow15 ? (0.0231509991f - (0.000360000005f * fSlow13)) : (0.0229710005f - (0.00700200023f * fSlow16)));
		float fSlow338 = (iSlow12 ? (iSlow15 ? (0.0183559991f - (0.00738999993f * fSlow13)) : ((0.00468300004f * fSlow16) + 0.0146610001f)) : fSlow337);
		float fSlow339 = std::pow(0.00100000005f, (fConst5 / (fSlow338 + (fSlow19 * ((iSlow12 ? fSlow337 : (iSlow15 ? ((0.012542f * fSlow13) + 0.0198749993f) : (0.0261460003f - (0.00559000019f * fSlow16)))) - fSlow338)))));
		float fSlow340 = (0.0f - (2.0f * fSlow339));
		float fSlow341 = (iSlow15 ? ((8835.7002f * fSlow13) + 5880.95459f) : (10298.8047f - (1319.40906f * fSlow16)));
		float fSlow342 = (iSlow12 ? (iSlow15 ? ((1625.83264f * fSlow13) + 6415.07178f) : ((2478.46313f * fSlow16) + 7227.98828f)) : fSlow341);
		float fSlow343 = std::cos((fConst6 * (fSlow342 + (fSlow19 * ((iSlow12 ? fSlow341 : (iSlow15 ? (5636.81787f - (873.069763f * fSlow13)) : ((1476.76941f * fSlow16) + 5200.2832f))) - fSlow342)))));
		float fSlow344 = mydsp_faustpower2_f(fSlow339);
		float fSlow345 = (iSlow15 ? (0.0683669969f - (0.043370001f * fSlow13)) : (0.0466820002f - (0.0141430004f * fSlow16)));
		float fSlow346 = (iSlow12 ? (iSlow15 ? ((0.0171579998f * fSlow13) + 0.0811270028f) : (0.0897060037f - (0.0368469991f * fSlow16))) : fSlow345);
		float fSlow347 = (fSlow346 + (fSlow19 * ((iSlow12 ? fSlow345 : (iSlow15 ? ((0.0314880013f * fSlow13) + 0.0309250001f) : (0.0466689989f - (0.0139340004f * fSlow16)))) - fSlow346)));
		float fSlow348 = (iSlow15 ? (0.0233810004f - (0.0113220001f * fSlow13)) : (0.0177200008f - (0.00204599998f * fSlow16)));
		float fSlow349 = (iSlow12 ? (iSlow15 ? ((0.0287500005f * fSlow13) + 0.0186090004f) : (0.0329839997f - (0.0131569998f * fSlow16))) : fSlow348);
		float fSlow350 = std::pow(0.00100000005f, (fConst5 / (fSlow349 + (fSlow19 * ((iSlow12 ? fSlow348 : (iSlow15 ? (0.0286320001f - (0.0196620002f * fSlow13)) : ((0.00577600021f * fSlow16) + 0.018801f))) - fSlow349)))));
		float fSlow351 = (0.0f - (2.0f * fSlow350));
		float fSlow352 = (iSlow15 ? ((8938.48047f * fSlow13) + 6095.2915f) : (10564.5322f - (489.282471f * fSlow16)));
		float fSlow353 = (iSlow12 ? (iSlow15 ? ((1591.84314f * fSlow13) + 6552.42285f) : ((2510.54492f * fSlow16) + 7348.34473f)) : fSlow352);
		float fSlow354 = std::cos((fConst6 * (fSlow353 + (fSlow19 * ((iSlow12 ? fSlow352 : (iSlow15 ? (5983.62891f - (1070.57947f * fSlow13)) : ((1784.76135f * fSlow16) + 5448.33936f))) - fSlow353)))));
		float fSlow355 = mydsp_faustpower2_f(fSlow350);
		float fSlow356 = (iSlow15 ? ((0.0214019995f * fSlow13) + 0.0237639993f) : (0.034465f - (0.024619f * fSlow16)));
		float fSlow357 = (iSlow12 ? (iSlow15 ? ((0.473753989f * fSlow13) + 0.0394220017f) : (0.276299f - (0.193388f * fSlow16))) : fSlow356);
		float fSlow358 = (fSlow357 + (fSlow19 * ((iSlow12 ? fSlow356 : (iSlow15 ? (0.0322149992f - (0.00217400002f * fSlow13)) : ((0.000809999998f * fSlow16) + 0.0311280005f))) - fSlow357)));
		float fSlow359 = (iSlow15 ? ((0.0217920002f * fSlow13) + 0.0212769993f) : (0.0321730003f - (0.0158680007f * fSlow16)));
		float fSlow360 = (iSlow12 ? (iSlow15 ? ((0.0203900002f * fSlow13) + 0.0175340008f) : (0.0277290009f - (0.00915800035f * fSlow16))) : fSlow359);
		float fSlow361 = std::pow(0.00100000005f, (fConst5 / (fSlow360 + (fSlow19 * ((iSlow12 ? fSlow359 : (iSlow15 ? (0.0323439986f - (0.0282039996f * fSlow13)) : ((0.00542700011f * fSlow16) + 0.0182419997f))) - fSlow360)))));
		float fSlow362 = (0.0f - (2.0f * fSlow361));
		float fSlow363 = (iSlow15 ? ((10366.166f * fSlow13) + 6432.60547f) : (11615.6885f - (1094.33752f * fSlow16)));
		float fSlow364 = (iSlow12 ? (iSlow15 ? ((3329.97534f * fSlow13) + 6785.46143f) : ((1629.97327f * fSlow16) + 8450.44922f)) : fSlow363);
		float fSlow365 = std::cos((fConst6 * (fSlow364 + (fSlow19 * ((iSlow12 ? fSlow363 : (iSlow15 ? (6104.01367f - (704.58783f * fSlow13)) : ((1768.3114f * fSlow16) + 5751.71973f))) - fSlow364)))));
		float fSlow366 = mydsp_faustpower2_f(fSlow361);
		float fSlow367 = (iSlow15 ? ((0.106012002f * fSlow13) + 0.0159239992f) : (0.0689300001f - (0.0613249987f * fSlow16)));
		float fSlow368 = (iSlow12 ? (iSlow15 ? (0.226010993f - (0.329658002f * fSlow13)) : (0.0611819997f - (0.0230260007f * fSlow16))) : fSlow367);
		float fSlow369 = (fSlow368 + (fSlow19 * ((iSlow12 ? fSlow367 : (iSlow15 ? (0.0321459994f - (0.00943200011f * fSlow13)) : (0.0274299998f - (0.00387599994f * fSlow16)))) - fSlow368)));
		float fSlow370 = (iSlow15 ? (0.0230570007f - (0.0153320003f * fSlow13)) : ((0.0113810003f * fSlow16) + 0.0153909996f));
		float fSlow371 = (iSlow12 ? (iSlow15 ? ((0.0127360001f * fSlow13) + 0.0186989997f) : (0.0250669997f - (0.00785399973f * fSlow16))) : fSlow370);
		float fSlow372 = std::pow(0.00100000005f, (fConst5 / (fSlow371 + (fSlow19 * ((iSlow12 ? fSlow370 : (iSlow15 ? (0.0337090008f - (0.0225380007f * fSlow13)) : ((0.00227400009f * fSlow16) + 0.0224399995f))) - fSlow371)))));
		float fSlow373 = (0.0f - (2.0f * fSlow372));
		float fSlow374 = (iSlow15 ? ((10919.5293f * fSlow13) + 6596.40332f) : (12056.168f - (91.3084412f * fSlow16)));
		float fSlow375 = (iSlow12 ? (iSlow15 ? ((4020.42407f * fSlow13) + 6990.10449f) : ((1251.68433f * fSlow16) + 9000.31641f)) : fSlow374);
		float fSlow376 = std::cos((fConst6 * (fSlow375 + (fSlow19 * ((iSlow12 ? fSlow374 : (iSlow15 ? (6184.54785f - (288.976532f * fSlow13)) : ((1637.84302f * fSlow16) + 6040.05957f))) - fSlow375)))));
		float fSlow377 = mydsp_faustpower2_f(fSlow372);
		float fSlow378 = (iSlow15 ? ((0.0966780037f * fSlow13) + 0.022163f) : (0.0705019981f - (0.0506360009f * fSlow16)));
		float fSlow379 = (iSlow12 ? (iSlow15 ? (0.0530130006f - (0.0281440001f * fSlow13)) : ((0.00713799987f * fSlow16) + 0.0389409997f)) : fSlow378);
		float fSlow380 = (fSlow379 + (fSlow19 * ((iSlow12 ? fSlow378 : (iSlow15 ? (0.0508619994f - (0.0369159989f * fSlow13)) : (0.0324040018f - (0.0148700001f * fSlow16)))) - fSlow379)));
		float fSlow381 = (iSlow15 ? (0.0202070009f - (0.0219800007f * fSlow13)) : ((0.00138000003f * fSlow16) + 0.00921699964f));
		float fSlow382 = (iSlow12 ? (iSlow15 ? ((0.0108979996f * fSlow13) + 0.0157619994f) : (0.0212110002f - (0.00220900006f * fSlow16))) : fSlow381);
		float fSlow383 = std::pow(0.00100000005f, (fConst5 / (fSlow382 + (fSlow19 * ((iSlow12 ? fSlow381 : (iSlow15 ? (0.0249380004f - (0.0079979999f * fSlow13)) : ((0.00348099996f * fSlow16) + 0.020939f))) - fSlow382)))));
		float fSlow384 = (0.0f - (2.0f * fSlow383));
		float fSlow385 = (iSlow15 ? ((11680.5752f * fSlow13) + 6820.91748f) : ((1566.00818f * fSlow16) + 12661.2051f));
		float fSlow386 = (iSlow12 ? (iSlow15 ? ((7348.42236f * fSlow13) + 7256.1167f) : (10930.3271f - (540.462646f * fSlow16))) : fSlow385);
		float fSlow387 = std::cos((fConst6 * (fSlow386 + (fSlow19 * ((iSlow12 ? fSlow385 : (iSlow15 ? (6602.61475f - (203.899292f * fSlow13)) : ((1304.47351f * fSlow16) + 6500.66504f))) - fSlow386)))));
		float fSlow388 = mydsp_faustpower2_f(fSlow383);
		float fSlow389 = (iSlow15 ? ((0.0159159992f * fSlow13) + 0.0179539993f) : (0.0259119999f - (0.0183290001f * fSlow16)));
		float fSlow390 = (iSlow12 ? (iSlow15 ? (0.0526200011f - (0.0143459998f * fSlow13)) : (0.0454469994f - (0.0106079997f * fSlow16))) : fSlow389);
		float fSlow391 = (fSlow390 + (fSlow19 * ((iSlow12 ? fSlow389 : (iSlow15 ? ((0.00298999995f * fSlow13) + 0.0168609992f) : (0.0183559991f - (0.00108800002f * fSlow16)))) - fSlow390)));
		float fSlow392 = (iSlow15 ? ((0.0185279995f * fSlow13) + 0.0196720008f) : (0.0289360005f - (0.0190099999f * fSlow16)));
		float fSlow393 = (iSlow12 ? (iSlow15 ? (0.0228000004f - (0.0117800003f * fSlow13)) : ((0.0035300001f * fSlow16) + 0.0169099998f)) : fSlow392);
		float fSlow394 = std::pow(0.00100000005f, (fConst5 / (fSlow393 + (fSlow19 * ((iSlow12 ? fSlow392 : (iSlow15 ? (0.0638329983f - (0.103791997f * fSlow13)) : ((0.0057959999f * fSlow16) + 0.0119369999f))) - fSlow393)))));
		float fSlow395 = (0.0f - (2.0f * fSlow394));
		float fSlow396 = (iSlow15 ? ((11938.7012f * fSlow13) + 6907.05518f) : ((2625.04956f * fSlow16) + 12876.4053f));
		float fSlow397 = (iSlow12 ? (iSlow15 ? ((6773.88525f * fSlow13) + 7884.5083f) : ((1056.44104f * fSlow16) + 11271.4512f)) : fSlow396);
		float fSlow398 = std::cos((fConst6 * (fSlow397 + (fSlow19 * ((iSlow12 ? fSlow396 : (iSlow15 ? ((125.271469f * fSlow13) + 6718.24756f) : ((3138.02246f * fSlow16) + 6780.8833f))) - fSlow397)))));
		float fSlow399 = mydsp_faustpower2_f(fSlow394);
		float fSlow400 = (iSlow15 ? ((0.0923419967f * fSlow13) + 0.0299169999f) : (0.0760879964f - (0.0670970008f * fSlow16)));
		float fSlow401 = (iSlow12 ? (iSlow15 ? ((0.00298199989f * fSlow13) + 0.041956f) : (0.043446999f - (0.0207090005f * fSlow16))) : fSlow400);
		float fSlow402 = (fSlow401 + (fSlow19 * ((iSlow12 ? fSlow400 : (iSlow15 ? ((0.0153179998f * fSlow13) + 0.0192280002f) : (0.0268869996f - (0.000684999977f * fSlow16)))) - fSlow401)));
		float fSlow403 = (iSlow15 ? (0.0163579993f - (0.00892600045f * fSlow13)) : (0.011895f - (0.00430000015f * fSlow16)));
		float fSlow404 = (iSlow12 ? (iSlow15 ? ((0.0286740009f * fSlow13) + 0.0131510003f) : (0.0274880007f - (0.0061590001f * fSlow16))) : fSlow403);
		float fSlow405 = std::pow(0.00100000005f, (fConst5 / (fSlow404 + (fSlow19 * ((iSlow12 ? fSlow403 : (iSlow15 ? (0.0322970003f - (0.0411159992f * fSlow13)) : ((0.0061420002f * fSlow16) + 0.0117389997f))) - fSlow404)))));
		float fSlow406 = (0.0f - (2.0f * fSlow405));
		float fSlow407 = (iSlow15 ? ((12104.1211f * fSlow13) + 7030.82959f) : ((2504.96265f * fSlow16) + 13082.8906f));
		float fSlow408 = (iSlow12 ? (iSlow15 ? ((5261.64502f * fSlow13) + 8787.47949f) : ((1047.17322f * fSlow16) + 11418.3018f)) : fSlow407);
		float fSlow409 = std::cos((fConst6 * (fSlow408 + (fSlow19 * ((iSlow12 ? fSlow407 : (iSlow15 ? ((85.7768631f * fSlow13) + 6835.84424f) : ((3540.25586f * fSlow16) + 6878.73242f))) - fSlow408)))));
		float fSlow410 = mydsp_faustpower2_f(fSlow405);
		float fSlow411 = (iSlow15 ? ((0.0070460001f * fSlow13) + 0.0214489996f) : (0.0249719992f - (0.0157779995f * fSlow16)));
		float fSlow412 = (iSlow12 ? (iSlow15 ? (0.0581469983f - (0.0136000002f * fSlow13)) : (0.0513469987f - (0.0268670004f * fSlow16))) : fSlow411);
		float fSlow413 = (fSlow412 + (fSlow19 * ((iSlow12 ? fSlow411 : (iSlow15 ? ((0.0391499996f * fSlow13) + 0.0214280002f) : (0.041003f - (0.0272780005f * fSlow16)))) - fSlow412)));
		float fSlow414 = (iSlow15 ? (0.0247569997f - (0.0242999997f * fSlow13)) : (0.0126069998f - (0.0039309999f * fSlow16)));
		float fSlow415 = (iSlow12 ? (iSlow15 ? ((0.001728f * fSlow13) + 0.0122999996f) : ((0.00986300036f * fSlow16) + 0.0131639997f)) : fSlow414);
		float fSlow416 = std::pow(0.00100000005f, (fConst5 / (fSlow415 + (fSlow19 * ((iSlow12 ? fSlow414 : (iSlow15 ? (0.0284729991f - (0.0163180009f * fSlow13)) : (0.0203140005f - (0.00159899995f * fSlow16)))) - fSlow415)))));
		float fSlow417 = (0.0f - (2.0f * fSlow416));
		float fSlow418 = (iSlow15 ? ((13027.1084f * fSlow13) + 7337.88281f) : ((2438.70166f * fSlow16) + 13851.4375f));
		float fSlow419 = (iSlow12 ? (iSlow15 ? ((5837.07275f * fSlow13) + 10529.8496f) : ((42.8020935f * fSlow16) + 13448.3857f)) : fSlow418);
		float fSlow420 = std::cos((fConst6 * (fSlow419 + (fSlow19 * ((iSlow12 ? fSlow418 : (iSlow15 ? ((490.418884f * fSlow13) + 6882.25439f) : ((4168.63818f * fSlow16) + 7127.46387f))) - fSlow419)))));
		float fSlow421 = mydsp_faustpower2_f(fSlow416);
		float fSlow422 = (iSlow15 ? ((0.0388359986f * fSlow13) + 0.0190830007f) : (0.0385009982f - (0.0283729993f * fSlow16)));
		float fSlow423 = (iSlow12 ? (iSlow15 ? (0.0612620004f - (0.0112300003f * fSlow13)) : ((0.102408998f * fSlow16) + 0.0556470007f)) : fSlow422);
		float fSlow424 = (fSlow423 + (fSlow19 * ((iSlow12 ? fSlow422 : (iSlow15 ? (0.0210389998f - (0.0165199991f * fSlow13)) : ((0.00283199991f * fSlow16) + 0.0127790002f))) - fSlow423)));
		float fSlow425 = (iSlow15 ? ((0.00221000006f * fSlow13) + 0.0170360003f) : (0.0181409996f - (0.00986700039f * fSlow16)));
		float fSlow426 = (iSlow12 ? (iSlow15 ? (0.0181140006f - (0.0115780002f * fSlow13)) : ((0.0065080002f * fSlow16) + 0.012325f)) : fSlow425);
		float fSlow427 = std::pow(0.00100000005f, (fConst5 / (fSlow426 + (fSlow19 * ((iSlow12 ? fSlow425 : (iSlow15 ? (0.0257680006f - (0.0238400009f * fSlow13)) : ((0.00388900004f * fSlow16) + 0.0138480002f))) - fSlow426)))));
		float fSlow428 = (0.0f - (2.0f * fSlow427));
		float fSlow429 = (iSlow15 ? ((13699.2881f * fSlow13) + 7602.73926f) : ((1965.78967f * fSlow16) + 14452.3828f));
		float fSlow430 = (iSlow12 ? (iSlow15 ? ((6593.74414f * fSlow13) + 10641.8623f) : ((1133.55725f * fSlow16) + 13938.7344f)) : fSlow429);
		float fSlow431 = std::cos((fConst6 * (fSlow430 + (fSlow19 * ((iSlow12 ? fSlow429 : (iSlow15 ? ((960.501282f * fSlow13) + 7220.7749f) : ((3731.69434f * fSlow16) + 7701.02539f))) - fSlow430)))));
		float fSlow432 = mydsp_faustpower2_f(fSlow427);
		float fSlow433 = (iSlow15 ? ((0.0501179993f * fSlow13) + 0.0260760002f) : (0.0511349998f - (0.0425780006f * fSlow16)));
		float fSlow434 = (iSlow12 ? (iSlow15 ? ((0.0514359996f * fSlow13) + 0.0461179987f) : (0.0718360022f - (0.0449879989f * fSlow16))) : fSlow433);
		float fSlow435 = (fSlow434 + (fSlow19 * ((iSlow12 ? fSlow433 : (iSlow15 ? ((0.0235939994f * fSlow13) + 0.0169879999f) : (0.0287849996f - (0.007491f * fSlow16)))) - fSlow434)));
		float fSlow436 = (iSlow15 ? ((0.00348199997f * fSlow13) + 0.0165999997f) : (0.0183409993f - (0.00687000016f * fSlow16)));
		float fSlow437 = (iSlow12 ? (iSlow15 ? ((0.0135859996f * fSlow13) + 0.0131919999f) : (0.0199849997f - (0.00164100004f * fSlow16))) : fSlow436);
		float fSlow438 = std::pow(0.00100000005f, (fConst5 / (fSlow437 + (fSlow19 * ((iSlow12 ? fSlow436 : (iSlow15 ? (0.0248770006f - (0.0167459995f * fSlow13)) : (0.0165040009f - (0.000844000024f * fSlow16)))) - fSlow437)))));
		float fSlow439 = (0.0f - (2.0f * fSlow438));
		float fSlow440 = (iSlow15 ? ((15514.1475f * fSlow13) + 7926.83643f) : ((979.356445f * fSlow16) + 15683.9102f));
		float fSlow441 = (iSlow12 ? (iSlow15 ? ((4518.75342f * fSlow13) + 12075.0176f) : ((842.352051f * fSlow16) + 14334.3945f)) : fSlow440);
		float fSlow442 = std::cos((fConst6 * (fSlow441 + (fSlow19 * ((iSlow12 ? fSlow440 : (iSlow15 ? ((6108.71924f * fSlow13) + 7283.26416f) : ((3084.61475f * fSlow16) + 10337.624f))) - fSlow441)))));
		float fSlow443 = mydsp_faustpower2_f(fSlow438);
		float fSlow444 = (iSlow15 ? ((0.0196720008f * fSlow13) + 0.0179650001f) : (0.0278009996f - (0.018468f * fSlow16)));
		float fSlow445 = (iSlow12 ? (iSlow15 ? ((0.00511399982f * fSlow13) + 0.0382560007f) : (0.040812999f - (0.0128039997f * fSlow16))) : fSlow444);
		float fSlow446 = (fSlow445 + (fSlow19 * ((iSlow12 ? fSlow444 : (iSlow15 ? (0.0179709997f - (0.00925000012f * fSlow13)) : (0.0133459996f - (0.00185999996f * fSlow16)))) - fSlow445)));
		float fSlow447 = (iSlow15 ? ((0.0159699991f * fSlow13) + 0.0101950001f) : (0.0181799997f - (0.00575600006f * fSlow16)));
		float fSlow448 = (iSlow12 ? (iSlow15 ? (0.0856700018f - (0.0124840001f * fSlow13)) : (0.0794280022f - (0.0606169999f * fSlow16))) : fSlow447);
		float fSlow449 = std::pow(0.00100000005f, (fConst5 / (fSlow448 + (fSlow19 * ((iSlow12 ? fSlow447 : (iSlow15 ? ((0.118890002f * fSlow13) + 0.026385f) : (0.085830003f - (0.0693660006f * fSlow16)))) - fSlow448)))));
		float fSlow450 = (0.0f - (2.0f * fSlow449));
		float fSlow451 = (iSlow15 ? ((8839.20996f * fSlow13) + 12248.3457f) : ((1323.66406f * fSlow16) + 16667.9512f));
		float fSlow452 = (iSlow12 ? (iSlow15 ? ((16.5578289f * fSlow13) + 17405.1699f) : ((2729.85278f * fSlow16) + 17413.4492f)) : fSlow451);
		float fSlow453 = std::cos((fConst6 * (fSlow452 + (fSlow19 * ((iSlow12 ? fSlow451 : (iSlow15 ? ((20006.6953f * fSlow13) + 7407.67188f) : (17411.0195f - (3731.78687f * fSlow16)))) - fSlow452)))));
		float fSlow454 = mydsp_faustpower2_f(fSlow449);
		float fSlow455 = (iSlow15 ? ((0.0109019997f * fSlow13) + 0.0170179997f) : (0.0224690009f - (0.0149750002f * fSlow16)));
		float fSlow456 = (iSlow12 ? (iSlow15 ? (0.124150999f - (0.114596002f * fSlow13)) : (0.0668530017f - (0.0354660004f * fSlow16))) : fSlow455);
		float fSlow457 = (fSlow456 + (fSlow19 * ((iSlow12 ? fSlow455 : (iSlow15 ? (0.0330649987f - (0.0315679982f * fSlow13)) : (0.0172809996f - (0.00540600019f * fSlow16)))) - fSlow456)));
		for (int i = 0; (i < count); i = (i + 1)) {
			iRec14[0] = 0;
			int iRec15 = iRec14[1];
			float fRec19 = (float(iRec6[1]) - (0.997843683f * ((0.699999988f * fRec20[2]) + (0.150000006f * (fRec20[1] + fRec20[3])))));
			fRec30[0] = (fSlow1 + (0.999000013f * fRec30[1]));
			fVec0[0] = fSlow4;
			float fTemp0 = float(((fSlow4 == fVec0[1]) | iSlow5));
			fRec31[0] = ((0.999000013f * (fRec31[1] * fTemp0)) + (fSlow6 * (1.0f - (0.999000013f * fTemp0))));
			float fTemp1 = ((fSlow3 / fRec31[0]) + -0.100000001f);
			float fTemp2 = (fConst2 * ((1.0f - fRec30[0]) * fTemp1));
			float fTemp3 = (fTemp2 + -1.49999499f);
			int iTemp4 = int(fTemp3);
			int iTemp5 = int(std::min<float>(fConst1, float(std::max<int>(0, int(iTemp4)))));
			float fTemp6 = std::floor(fTemp3);
			float fTemp7 = (fTemp2 + (-1.0f - fTemp6));
			float fTemp8 = (0.0f - fTemp7);
			float fTemp9 = (fTemp2 + (-2.0f - fTemp6));
			float fTemp10 = (0.0f - (0.5f * fTemp9));
			float fTemp11 = (fTemp2 + (-3.0f - fTemp6));
			float fTemp12 = (0.0f - (0.333333343f * fTemp11));
			float fTemp13 = (fTemp2 + (-4.0f - fTemp6));
			float fTemp14 = (0.0f - (0.25f * fTemp13));
			float fTemp15 = (fTemp2 - fTemp6);
			int iTemp16 = int(std::min<float>(fConst1, float(std::max<int>(0, int((iTemp4 + 1))))));
			float fTemp17 = (0.0f - fTemp9);
			float fTemp18 = (0.0f - (0.5f * fTemp11));
			float fTemp19 = (0.0f - (0.333333343f * fTemp13));
			int iTemp20 = int(std::min<float>(fConst1, float(std::max<int>(0, int((iTemp4 + 2))))));
			float fTemp21 = (0.0f - fTemp11);
			float fTemp22 = (0.0f - (0.5f * fTemp13));
			float fTemp23 = (fTemp7 * fTemp9);
			int iTemp24 = int(std::min<float>(fConst1, float(std::max<int>(0, int((iTemp4 + 3))))));
			float fTemp25 = (0.0f - fTemp13);
			float fTemp26 = (fTemp23 * fTemp11);
			int iTemp27 = int(std::min<float>(fConst1, float(std::max<int>(0, int((iTemp4 + 4))))));
			fRec27[0] = (((((fRec2[((IOTA - (iTemp5 + 1)) & 2047)] * fTemp8) * fTemp10) * fTemp12) * fTemp14) + (fTemp15 * ((((((fRec2[((IOTA - (iTemp16 + 1)) & 2047)] * fTemp17) * fTemp18) * fTemp19) + (0.5f * (((fTemp7 * fRec2[((IOTA - (iTemp20 + 1)) & 2047)]) * fTemp21) * fTemp22))) + (0.166666672f * ((fTemp23 * fRec2[((IOTA - (iTemp24 + 1)) & 2047)]) * fTemp25))) + (0.0416666679f * (fTemp26 * fRec2[((IOTA - (iTemp27 + 1)) & 2047)])))));
			fRec32[0] = ((0.0500000007f * fRec32[1]) + (0.949999988f * fRec27[1]));
			float fRec28 = fRec32[0];
			fRec34[0] = fRec0[1];
			fRec35[(IOTA & 2047)] = (-1.0f * (0.997843683f * ((0.699999988f * fRec34[2]) + (0.150000006f * (fRec34[1] + fRec34[3])))));
			float fTemp28 = (fConst2 * (fRec30[0] * fTemp1));
			float fTemp29 = (fTemp28 + -1.49999499f);
			int iTemp30 = int(fTemp29);
			int iTemp31 = int(std::min<float>(fConst1, float(std::max<int>(0, int(iTemp30)))));
			float fTemp32 = std::floor(fTemp29);
			float fTemp33 = (fTemp28 + (-1.0f - fTemp32));
			float fTemp34 = (0.0f - fTemp33);
			float fTemp35 = (fTemp28 + (-2.0f - fTemp32));
			float fTemp36 = (0.0f - (0.5f * fTemp35));
			float fTemp37 = (fTemp28 + (-3.0f - fTemp32));
			float fTemp38 = (0.0f - (0.333333343f * fTemp37));
			float fTemp39 = (fTemp28 + (-4.0f - fTemp32));
			float fTemp40 = (0.0f - (0.25f * fTemp39));
			float fTemp41 = (fTemp28 - fTemp32);
			int iTemp42 = int(std::min<float>(fConst1, float(std::max<int>(0, int((iTemp30 + 1))))));
			float fTemp43 = (0.0f - fTemp35);
			float fTemp44 = (0.0f - (0.5f * fTemp37));
			float fTemp45 = (0.0f - (0.333333343f * fTemp39));
			int iTemp46 = int(std::min<float>(fConst1, float(std::max<int>(0, int((iTemp30 + 2))))));
			float fTemp47 = (0.0f - fTemp37);
			float fTemp48 = (0.0f - (0.5f * fTemp39));
			float fTemp49 = (fTemp33 * fTemp35);
			int iTemp50 = int(std::min<float>(fConst1, float(std::max<int>(0, int((iTemp30 + 3))))));
			float fTemp51 = (0.0f - fTemp39);
			float fTemp52 = (fTemp49 * fTemp37);
			int iTemp53 = int(std::min<float>(fConst1, float(std::max<int>(0, int((iTemp30 + 4))))));
			fVec1[0] = (((((fRec35[((IOTA - (iTemp31 + 2)) & 2047)] * fTemp34) * fTemp36) * fTemp38) * fTemp40) + (fTemp41 * ((((((fRec35[((IOTA - (iTemp42 + 2)) & 2047)] * fTemp43) * fTemp44) * fTemp45) + (0.5f * (((fTemp33 * fRec35[((IOTA - (iTemp46 + 2)) & 2047)]) * fTemp47) * fTemp48))) + (0.166666672f * ((fTemp49 * fRec35[((IOTA - (iTemp50 + 2)) & 2047)]) * fTemp51))) + (0.0416666679f * (fTemp52 * fRec35[((IOTA - (iTemp53 + 2)) & 2047)])))));
			iRec37[0] = ((1103515245 * iRec37[1]) + 12345);
			float fTemp54 = std::tan((fSlow8 * fRec31[0]));
			float fTemp55 = (1.0f / fTemp54);
			float fTemp56 = (((fTemp55 + 1.41421354f) / fTemp54) + 1.0f);
			fRec36[0] = ((4.65661287e-10f * float(iRec37[0])) - (((fRec36[2] * (((fTemp55 + -1.41421354f) / fTemp54) + 1.0f)) + (2.0f * (fRec36[1] * (1.0f - (1.0f / mydsp_faustpower2_f(fTemp54)))))) / fTemp56));
			iRec38[0] = (((iRec38[1] + (iRec38[1] > 0)) * (fSlow4 <= fVec0[1])) + (fSlow4 > fVec0[1]));
			float fTemp57 = (float(iRec38[0]) / std::max<float>(1.0f, (fConst4 * mydsp_faustpower2_f((1.0f - (fSlow9 * fRec31[0]))))));
			float fTemp58 = (fSlow7 * (((fRec36[2] + (fRec36[0] + (2.0f * fRec36[1]))) * std::max<float>(0.0f, std::min<float>(fTemp57, (2.0f - fTemp57)))) / fTemp56));
			fVec2[0] = (fVec1[1] + fTemp58);
			fRec33[(IOTA & 2047)] = ((0.0500000007f * fRec33[((IOTA - 1) & 2047)]) + (0.949999988f * fVec2[1]));
			float fRec29 = (((((fTemp8 * fTemp10) * fTemp12) * fTemp14) * fRec33[((IOTA - iTemp5) & 2047)]) + (fTemp15 * ((((((fTemp17 * fTemp18) * fTemp19) * fRec33[((IOTA - iTemp16) & 2047)]) + (0.5f * (((fTemp7 * fTemp21) * fTemp22) * fRec33[((IOTA - iTemp20) & 2047)]))) + (0.166666672f * ((fTemp23 * fTemp25) * fRec33[((IOTA - iTemp24) & 2047)]))) + (0.0416666679f * (fTemp26 * fRec33[((IOTA - iTemp27) & 2047)])))));
			fRec24[0] = fRec28;
			float fRec25 = (fTemp58 + fRec24[1]);
			float fRec26 = fRec29;
			fRec21[(IOTA & 2047)] = fRec25;
			float fRec22 = (((((fTemp34 * fTemp36) * fTemp38) * fTemp40) * fRec21[((IOTA - (iTemp31 + 1)) & 2047)]) + (fTemp41 * ((((((fTemp43 * fTemp44) * fTemp45) * fRec21[((IOTA - (iTemp42 + 1)) & 2047)]) + (0.5f * (((fTemp33 * fTemp47) * fTemp48) * fRec21[((IOTA - (iTemp46 + 1)) & 2047)]))) + (0.166666672f * ((fTemp49 * fTemp51) * fRec21[((IOTA - (iTemp50 + 1)) & 2047)]))) + (0.0416666679f * (fTemp52 * fRec21[((IOTA - (iTemp53 + 1)) & 2047)])))));
			fRec23[0] = fRec26;
			fRec20[0] = fRec23[1];
			fVec3[0] = fSlow10;
			float fTemp59 = (fSlow10 - fVec3[1]);
			fVec4[0] = (fRec20[1] + (fTemp59 * float((fTemp59 > 0.0f))));
			fRec18[0] = (fVec4[1] - (((fRec18[1] * fSlow21) * fSlow24) + (fSlow25 * fRec18[2])));
			fRec39[0] = (fVec4[1] - (((fRec39[1] * fSlow32) * fSlow35) + (fSlow36 * fRec39[2])));
			fRec40[0] = (fVec4[1] - (((fRec40[1] * fSlow43) * fSlow46) + (fSlow47 * fRec40[2])));
			fRec41[0] = (fVec4[1] - (((fRec41[1] * fSlow54) * fSlow57) + (fSlow58 * fRec41[2])));
			fRec42[0] = (fVec4[1] - (((fRec42[1] * fSlow65) * fSlow68) + (fSlow69 * fRec42[2])));
			fRec43[0] = (fVec4[1] - (((fRec43[1] * fSlow76) * fSlow79) + (fSlow80 * fRec43[2])));
			fRec44[0] = (fVec4[1] - (((fRec44[1] * fSlow87) * fSlow90) + (fSlow91 * fRec44[2])));
			fRec45[0] = (fVec4[1] - (((fRec45[1] * fSlow98) * fSlow101) + (fSlow102 * fRec45[2])));
			fRec46[0] = (fVec4[1] - (((fRec46[1] * fSlow109) * fSlow112) + (fSlow113 * fRec46[2])));
			fRec47[0] = (fVec4[1] - (((fRec47[1] * fSlow120) * fSlow123) + (fSlow124 * fRec47[2])));
			fRec48[0] = (fVec4[1] - (((fRec48[1] * fSlow131) * fSlow134) + (fSlow135 * fRec48[2])));
			fRec49[0] = (fVec4[1] - (((fRec49[1] * fSlow142) * fSlow145) + (fSlow146 * fRec49[2])));
			fRec50[0] = (fVec4[1] - (((fRec50[1] * fSlow153) * fSlow156) + (fSlow157 * fRec50[2])));
			fRec51[0] = (fVec4[1] - (((fRec51[1] * fSlow164) * fSlow167) + (fSlow168 * fRec51[2])));
			fRec52[0] = (fVec4[1] - (((fRec52[1] * fSlow175) * fSlow178) + (fSlow179 * fRec52[2])));
			fRec53[0] = (fVec4[1] - (((fRec53[1] * fSlow186) * fSlow189) + (fSlow190 * fRec53[2])));
			fRec54[0] = (fVec4[1] - (((fRec54[1] * fSlow197) * fSlow200) + (fSlow201 * fRec54[2])));
			fRec55[0] = (fVec4[1] - (((fRec55[1] * fSlow208) * fSlow211) + (fSlow212 * fRec55[2])));
			fRec56[0] = (fVec4[1] - (((fRec56[1] * fSlow219) * fSlow222) + (fSlow223 * fRec56[2])));
			fRec57[0] = (fVec4[1] - (((fRec57[1] * fSlow230) * fSlow233) + (fSlow234 * fRec57[2])));
			fRec58[0] = (fVec4[1] - (((fRec58[1] * fSlow241) * fSlow244) + (fSlow245 * fRec58[2])));
			fRec59[0] = (fVec4[1] - (((fRec59[1] * fSlow252) * fSlow255) + (fSlow256 * fRec59[2])));
			fRec60[0] = (fVec4[1] - (((fRec60[1] * fSlow263) * fSlow266) + (fSlow267 * fRec60[2])));
			fRec61[0] = (fVec4[1] - (((fRec61[1] * fSlow274) * fSlow277) + (fSlow278 * fRec61[2])));
			fRec62[0] = (fVec4[1] - (((fRec62[1] * fSlow285) * fSlow288) + (fSlow289 * fRec62[2])));
			fRec63[0] = (fVec4[1] - (((fRec63[1] * fSlow296) * fSlow299) + (fSlow300 * fRec63[2])));
			fRec64[0] = (fVec4[1] - (((fRec64[1] * fSlow307) * fSlow310) + (fSlow311 * fRec64[2])));
			fRec65[0] = (fVec4[1] - (((fRec65[1] * fSlow318) * fSlow321) + (fSlow322 * fRec65[2])));
			fRec66[0] = (fVec4[1] - (((fRec66[1] * fSlow329) * fSlow332) + (fSlow333 * fRec66[2])));
			fRec67[0] = (fVec4[1] - (((fRec67[1] * fSlow340) * fSlow343) + (fSlow344 * fRec67[2])));
			fRec68[0] = (fVec4[1] - (((fRec68[1] * fSlow351) * fSlow354) + (fSlow355 * fRec68[2])));
			fRec69[0] = (fVec4[1] - (((fRec69[1] * fSlow362) * fSlow365) + (fSlow366 * fRec69[2])));
			fRec70[0] = (fVec4[1] - (((fRec70[1] * fSlow373) * fSlow376) + (fSlow377 * fRec70[2])));
			fRec71[0] = (fVec4[1] - (((fRec71[1] * fSlow384) * fSlow387) + (fSlow388 * fRec71[2])));
			fRec72[0] = (fVec4[1] - (((fRec72[1] * fSlow395) * fSlow398) + (fSlow399 * fRec72[2])));
			fRec73[0] = (fVec4[1] - (((fRec73[1] * fSlow406) * fSlow409) + (fSlow410 * fRec73[2])));
			fRec74[0] = (fVec4[1] - (((fRec74[1] * fSlow417) * fSlow420) + (fSlow421 * fRec74[2])));
			fRec75[0] = (fVec4[1] - (((fRec75[1] * fSlow428) * fSlow431) + (fSlow432 * fRec75[2])));
			fRec76[0] = (fVec4[1] - (((fRec76[1] * fSlow439) * fSlow442) + (fSlow443 * fRec76[2])));
			fRec77[0] = (fVec4[1] - (((fRec77[1] * fSlow450) * fSlow453) + (fSlow454 * fRec77[2])));
			float fTemp60 = (0.0250000004f * (((((((((((((((((((((((((((((((((((((((((fRec18[0] - fRec18[2]) * fSlow28) + ((fRec39[0] - fRec39[2]) * fSlow39)) + ((fRec40[0] - fRec40[2]) * fSlow50)) + ((fRec41[0] - fRec41[2]) * fSlow61)) + ((fRec42[0] - fRec42[2]) * fSlow72)) + ((fRec43[0] - fRec43[2]) * fSlow83)) + ((fRec44[0] - fRec44[2]) * fSlow94)) + ((fRec45[0] - fRec45[2]) * fSlow105)) + ((fRec46[0] - fRec46[2]) * fSlow116)) + ((fRec47[0] - fRec47[2]) * fSlow127)) + ((fRec48[0] - fRec48[2]) * fSlow138)) + ((fRec49[0] - fRec49[2]) * fSlow149)) + ((fRec50[0] - fRec50[2]) * fSlow160)) + ((fRec51[0] - fRec51[2]) * fSlow171)) + ((fRec52[0] - fRec52[2]) * fSlow182)) + ((fRec53[0] - fRec53[2]) * fSlow193)) + ((fRec54[0] - fRec54[2]) * fSlow204)) + ((fRec55[0] - fRec55[2]) * fSlow215)) + ((fRec56[0] - fRec56[2]) * fSlow226)) + ((fRec57[0] - fRec57[2]) * fSlow237)) + ((fRec58[0] - fRec58[2]) * fSlow248)) + ((fRec59[0] - fRec59[2]) * fSlow259)) + ((fRec60[0] - fRec60[2]) * fSlow270)) + ((fRec61[0] - fRec61[2]) * fSlow281)) + ((fRec62[0] - fRec62[2]) * fSlow292)) + ((fRec63[0] - fRec63[2]) * fSlow303)) + ((fRec64[0] - fRec64[2]) * fSlow314)) + ((fRec65[0] - fRec65[2]) * fSlow325)) + ((fRec66[0] - fRec66[2]) * fSlow336)) + ((fRec67[0] - fRec67[2]) * fSlow347)) + ((fRec68[0] - fRec68[2]) * fSlow358)) + ((fRec69[0] - fRec69[2]) * fSlow369)) + ((fRec70[0] - fRec70[2]) * fSlow380)) + ((fRec71[0] - fRec71[2]) * fSlow391)) + ((fRec72[0] - fRec72[2]) * fSlow402)) + ((fRec73[0] - fRec73[2]) * fSlow413)) + ((fRec74[0] - fRec74[2]) * fSlow424)) + ((fRec75[0] - fRec75[2]) * fSlow435)) + ((fRec76[0] - fRec76[2]) * fSlow446)) + ((fRec77[0] - fRec77[2]) * fSlow457)));
			float fRec16 = fTemp60;
			float fRec17 = fTemp60;
			iRec10[0] = iRec15;
			int iRec11 = iRec10[1];
			float fRec12 = fRec16;
			float fRec13 = fRec17;
			iRec6[0] = iRec11;
			float fRec7 = fRec19;
			float fRec8 = fRec12;
			float fRec9 = fRec13;
			fRec2[(IOTA & 2047)] = fRec7;
			float fRec3 = fRec22;
			float fRec4 = fRec8;
			float fRec5 = fRec9;
			fRec0[0] = fRec3;
			float fRec1 = fRec5;
			float fTemp61 = (fSlow0 * fRec1);
			output0[i] = FAUSTFLOAT(fTemp61);
			output1[i] = FAUSTFLOAT(fTemp61);
			iRec14[1] = iRec14[0];
			fRec30[1] = fRec30[0];
			fVec0[1] = fVec0[0];
			fRec31[1] = fRec31[0];
			fRec27[1] = fRec27[0];
			fRec32[1] = fRec32[0];
			for (int j0 = 3; (j0 > 0); j0 = (j0 - 1)) {
				fRec34[j0] = fRec34[(j0 - 1)];
			}
			IOTA = (IOTA + 1);
			fVec1[1] = fVec1[0];
			iRec37[1] = iRec37[0];
			fRec36[2] = fRec36[1];
			fRec36[1] = fRec36[0];
			iRec38[1] = iRec38[0];
			fVec2[1] = fVec2[0];
			fRec24[1] = fRec24[0];
			fRec23[1] = fRec23[0];
			for (int j1 = 3; (j1 > 0); j1 = (j1 - 1)) {
				fRec20[j1] = fRec20[(j1 - 1)];
			}
			fVec3[1] = fVec3[0];
			fVec4[1] = fVec4[0];
			fRec18[2] = fRec18[1];
			fRec18[1] = fRec18[0];
			fRec39[2] = fRec39[1];
			fRec39[1] = fRec39[0];
			fRec40[2] = fRec40[1];
			fRec40[1] = fRec40[0];
			fRec41[2] = fRec41[1];
			fRec41[1] = fRec41[0];
			fRec42[2] = fRec42[1];
			fRec42[1] = fRec42[0];
			fRec43[2] = fRec43[1];
			fRec43[1] = fRec43[0];
			fRec44[2] = fRec44[1];
			fRec44[1] = fRec44[0];
			fRec45[2] = fRec45[1];
			fRec45[1] = fRec45[0];
			fRec46[2] = fRec46[1];
			fRec46[1] = fRec46[0];
			fRec47[2] = fRec47[1];
			fRec47[1] = fRec47[0];
			fRec48[2] = fRec48[1];
			fRec48[1] = fRec48[0];
			fRec49[2] = fRec49[1];
			fRec49[1] = fRec49[0];
			fRec50[2] = fRec50[1];
			fRec50[1] = fRec50[0];
			fRec51[2] = fRec51[1];
			fRec51[1] = fRec51[0];
			fRec52[2] = fRec52[1];
			fRec52[1] = fRec52[0];
			fRec53[2] = fRec53[1];
			fRec53[1] = fRec53[0];
			fRec54[2] = fRec54[1];
			fRec54[1] = fRec54[0];
			fRec55[2] = fRec55[1];
			fRec55[1] = fRec55[0];
			fRec56[2] = fRec56[1];
			fRec56[1] = fRec56[0];
			fRec57[2] = fRec57[1];
			fRec57[1] = fRec57[0];
			fRec58[2] = fRec58[1];
			fRec58[1] = fRec58[0];
			fRec59[2] = fRec59[1];
			fRec59[1] = fRec59[0];
			fRec60[2] = fRec60[1];
			fRec60[1] = fRec60[0];
			fRec61[2] = fRec61[1];
			fRec61[1] = fRec61[0];
			fRec62[2] = fRec62[1];
			fRec62[1] = fRec62[0];
			fRec63[2] = fRec63[1];
			fRec63[1] = fRec63[0];
			fRec64[2] = fRec64[1];
			fRec64[1] = fRec64[0];
			fRec65[2] = fRec65[1];
			fRec65[1] = fRec65[0];
			fRec66[2] = fRec66[1];
			fRec66[1] = fRec66[0];
			fRec67[2] = fRec67[1];
			fRec67[1] = fRec67[0];
			fRec68[2] = fRec68[1];
			fRec68[1] = fRec68[0];
			fRec69[2] = fRec69[1];
			fRec69[1] = fRec69[0];
			fRec70[2] = fRec70[1];
			fRec70[1] = fRec70[0];
			fRec71[2] = fRec71[1];
			fRec71[1] = fRec71[0];
			fRec72[2] = fRec72[1];
			fRec72[1] = fRec72[0];
			fRec73[2] = fRec73[1];
			fRec73[1] = fRec73[0];
			fRec74[2] = fRec74[1];
			fRec74[1] = fRec74[0];
			fRec75[2] = fRec75[1];
			fRec75[1] = fRec75[0];
			fRec76[2] = fRec76[1];
			fRec76[1] = fRec76[0];
			fRec77[2] = fRec77[1];
			fRec77[1] = fRec77[0];
			iRec10[1] = iRec10[0];
			iRec6[1] = iRec6[0];
			fRec0[1] = fRec0[0];
		}
	}

};

#ifdef FAUST_UIMACROS
	
	#define FAUST_FILE_NAME "modularInterpInstrMIDI.dsp"
	#define FAUST_CLASS_NAME "mydsp"
	#define FAUST_INPUTS 0
	#define FAUST_OUTPUTS 2
	#define FAUST_ACTIVES 10
	#define FAUST_PASSIVES 0

	FAUST_ADDHORIZONTALSLIDER("modularInterpInstr/[0]midi/freq", fHslider2, 440.0f, 50.0f, 1000.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("modularInterpInstr/[0]midi/bend", fHslider4, 0.0f, -2.0f, 2.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("modularInterpInstr/[0]midi/gain", fHslider5, 0.80000000000000004f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("modularInterpInstr/[0]midi/sustain", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f);
	FAUST_ADDHORIZONTALSLIDER("modularInterpInstr/[1]body/shape", fHslider7, 0.0f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("modularInterpInstr/[1]body/scale", fHslider6, 0.0f, 0.0f, 1.0f, 0.010999999999999999f);
	FAUST_ADDBUTTON("modularInterpInstr/[1]body/tapBody", fButton1);
	FAUST_ADDHORIZONTALSLIDER("modularInterpInstr/pluckPosition", fHslider1, 0.80000000000000004f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDHORIZONTALSLIDER("modularInterpInstr/outGain", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f);
	FAUST_ADDBUTTON("modularInterpInstr/gate", fButton0);

	#define FAUST_LIST_ACTIVES(p) \
		p(HORIZONTALSLIDER, freq, "modularInterpInstr/[0]midi/freq", fHslider2, 440.0f, 50.0f, 1000.0f, 0.01f) \
		p(HORIZONTALSLIDER, bend, "modularInterpInstr/[0]midi/bend", fHslider4, 0.0f, -2.0f, 2.0f, 0.01f) \
		p(HORIZONTALSLIDER, gain, "modularInterpInstr/[0]midi/gain", fHslider5, 0.80000000000000004f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, sustain, "modularInterpInstr/[0]midi/sustain", fHslider3, 0.0f, 0.0f, 1.0f, 1.0f) \
		p(HORIZONTALSLIDER, shape, "modularInterpInstr/[1]body/shape", fHslider7, 0.0f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, scale, "modularInterpInstr/[1]body/scale", fHslider6, 0.0f, 0.0f, 1.0f, 0.010999999999999999f) \
		p(BUTTON, tapBody, "modularInterpInstr/[1]body/tapBody", fButton1, 0.0, 0.0, 1.0, 1.0) \
		p(HORIZONTALSLIDER, pluckPosition, "modularInterpInstr/pluckPosition", fHslider1, 0.80000000000000004f, 0.0f, 1.0f, 0.01f) \
		p(HORIZONTALSLIDER, outGain, "modularInterpInstr/outGain", fHslider0, 0.5f, 0.0f, 1.0f, 0.01f) \
		p(BUTTON, gate, "modularInterpInstr/gate", fButton0, 0.0, 0.0, 1.0, 1.0) \

	#define FAUST_LIST_PASSIVES(p) \

#endif

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/

#define MULT_16 2147483647
#define DIV_16 4.6566129e-10

unsigned __exidx_start;
unsigned __exidx_end;

#if MIDICTRL
std::list<GUI*> GUI::fGuiList;
ztimedmap GUI::gTimedZoneMap;
#endif

modularInterpInstrMIDI::modularInterpInstrMIDI() : AudioStream(FAUST_INPUTS, new audio_block_t*[FAUST_INPUTS])
{
#ifdef NVOICES
    int nvoices = NVOICES;
    mydsp_poly* dsp_poly = new mydsp_poly(new mydsp(), nvoices, true, true);
    fDSP = dsp_poly;
#else
    fDSP = new mydsp();
#endif
    
    fDSP->init(AUDIO_SAMPLE_RATE_EXACT);
    
    fUI = new MapUI();
    fDSP->buildUserInterface(fUI);
    
    // allocating Faust inputs
    if (fDSP->getNumInputs() > 0) {
        fInChannel = new float*[fDSP->getNumInputs()];
        for (int i = 0; i < fDSP->getNumInputs(); i++) {
            fInChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
        }
    } else {
        fInChannel = NULL;
    }
    
    // allocating Faust outputs
    if (fDSP->getNumOutputs() > 0) {
        fOutChannel = new float*[fDSP->getNumOutputs()];
        for (int i = 0; i < fDSP->getNumOutputs(); i++) {
            fOutChannel[i] = new float[AUDIO_BLOCK_SAMPLES];
        }
    } else {
        fOutChannel = NULL;
    }
    
#if MIDICTRL
    fMIDIHandler = new teensy_midi();
#ifdef NVOICES
    fMIDIHandler->addMidiIn(dsp_poly);
#endif
    fMIDIInterface = new MidiUI(fMIDIHandler);
    fDSP->buildUserInterface(fMIDIInterface);
    fMIDIInterface->run();
#endif
}

modularInterpInstrMIDI::~modularInterpInstrMIDI()
{
    delete fDSP;
    delete fUI;
    for (int i = 0; i < fDSP->getNumInputs(); i++) {
        delete[] fInChannel[i];
    }
    delete [] fInChannel;
    for (int i = 0; i < fDSP->getNumOutputs(); i++) {
        delete[] fOutChannel[i];
    }
    delete [] fOutChannel;
#if MIDICTRL
    delete fMIDIInterface;
    delete fMIDIHandler;
#endif
}

template <int INPUTS, int OUTPUTS>
void modularInterpInstrMIDI::updateImp(void)
{
#if MIDICTRL
    // Process the MIDI messages received by the Teensy
    fMIDIHandler->processMidi();
    // Synchronize all GUI controllers
    GUI::updateAllGuis();
#endif
    
    if (INPUTS > 0) {
        audio_block_t* inBlock[INPUTS];
        for (int channel = 0; channel < INPUTS; channel++) {
            inBlock[channel] = receiveReadOnly(channel);
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                int32_t val = inBlock[channel]->data[i] << 16;
                fInChannel[channel][i] = val*DIV_16;
            }
            release(inBlock[channel]);
        }
    }
    
    fDSP->compute(AUDIO_BLOCK_SAMPLES, fInChannel, fOutChannel);
    
    for (int channel = 0; channel < OUTPUTS; channel++) {
        audio_block_t* outBlock[OUTPUTS];
        outBlock[channel] = allocate();
        if (outBlock[channel]) {
            for (int i = 0; i < AUDIO_BLOCK_SAMPLES; i++) {
                int32_t val = fOutChannel[channel][i]*MULT_16;
                outBlock[channel]->data[i] = val >> 16;
            }
            transmit(outBlock[channel], channel);
            release(outBlock[channel]);
        }
    }
}

void modularInterpInstrMIDI::update(void) { updateImp<FAUST_INPUTS, FAUST_OUTPUTS>(); }

void modularInterpInstrMIDI::setParamValue(const std::string& path, float value)
{
    fUI->setParamValue(path, value);
}

float modularInterpInstrMIDI::getParamValue(const std::string& path)
{
    return fUI->getParamValue(path);
}

/********************END ARCHITECTURE SECTION (part 2/2)****************/

#endif
