//------------------------------------------------------------------------------
// File: Tune.h
//
// Desc: Additional infrastructure to extend the tuner.idl.  Works nicely
//       from C++.
//
// Copyright (c) 1999 - 2001, Microsoft Corporation.  All rights reserved.
//------------------------------------------------------------------------------


#pragma once

#ifndef TUNE_H
#define TUNE_H

#include <tuner.h>

namespace BDATuningModel {

const long DEFAULT_MIN_CHANNEL = 2;
const long DEFAULT_MAX_CHANNEL = 999;
const long DEFAULT_MIN_FREQUENCY = 535;  //bottom us am
const long DEFAULT_MAX_FREQUENCY = 108000; // top us fm
const long DEFAULT_ANALOG_TUNER_COUNTRY_CODE = 1; //usa
const TunerInputType DEFAULT_ANALOG_TUNER_INPUT_TYPE = TunerInputCable; //usa

typedef CComQIPtr<ITuningSpaceContainer> PQTuningSpaceContainer;
typedef CComQIPtr<ITuningSpace> PQTuningSpace;
typedef CComQIPtr<IAnalogRadioTuningSpace> PQAnalogRadioTuningSpace;
typedef CComQIPtr<IAnalogTVTuningSpace> PQAnalogTVTuningSpace;
typedef CComQIPtr<IATSCTuningSpace> PQATSCTuningSpace;
typedef CComQIPtr<ITuneRequest> PQTuneRequest;
typedef CComQIPtr<IChannelTuneRequest> PQChannelTuneRequest;
typedef CComQIPtr<IATSCChannelTuneRequest> PQATSCChannelTuneRequest;
typedef CComQIPtr<ILocator> PQLocator;
typedef CComQIPtr<IATSCLocator> PQATSCLocator;
typedef CComQIPtr<IDVBTuningSpace> PQDVBTuningSpace;
typedef CComQIPtr<IDVBTuneRequest> PQDVBTuneRequest;
typedef CComQIPtr<IDVBSLocator> PQDVBSLocator;
typedef CComQIPtr<IDVBTLocator> PQDVBTLocator;
typedef CComQIPtr<IDVBCLocator> PQDVBCLocator;
typedef CComQIPtr<IAuxInTuningSpace> PQAuxInTuningSpace;

// tuning space container
class TNTuningSpaceContainer : public PQTuningSpaceContainer {
     TNTuningSpaceContainer() {}
     TNTuningSpaceContainer(const PQTuningSpaceContainer &a) : PQTuningSpaceContainer(a) {}
     TNTuningSpaceContainer(ITuningSpace *p) : PQTuningSpaceContainer(p) {}
     TNTuningSpaceContainer(IUnknown *p) : PQTuningSpaceContainer(p) {}
     TNTuningSpaceContainer(const TNTuningSpaceContainer &a) : PQTuningSpaceContainer(a) {}
     TNTuningSpaceContainer& operator=(TNTuningSpaceContainer& rhs) {
        PQTuningSpaceContainer::operator=(rhs);
        return *this;
    }

};

// tuning spaces
template<class TUNINGSPACETYPE, class TUNEREQUESTTYPE> class TNTuningSpaceHelper : public TUNINGSPACETYPE {
public:
    TNTuningSpaceHelper() {}
    TNTuningSpaceHelper(const TUNINGSPACETYPE &a) : TUNINGSPACETYPE(a) {}
    TNTuningSpaceHelper(ITuningSpace *p) : TUNINGSPACETYPE(p) {}
    TNTuningSpaceHelper(IUnknown *p) : TUNINGSPACETYPE(p) {}
    TNTuningSpaceHelper(const TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> &a) : TUNINGSPACETYPE(a) {}
    TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& rhs) {
        TUNINGSPACETYPE::operator=(rhs);
        return *this;
    }
    TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TUNINGSPACETYPE& rhs) {
        TUNINGSPACETYPE::operator=(rhs);
        return *this;
    }
    TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(IUnknown *rhs) {
        TUNINGSPACETYPE::operator=(rhs);
        return *this;
    }
    TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(ITuningSpace *rhs) {
        TUNINGSPACETYPE::operator=(rhs);
        return *this;
    }
    bool  operator==(TUNINGSPACETYPE& rhs) {
        CComBSTR rhsname;
        HRESULT hr = rhs->get_UniqueName(&rhsname);
        if (FAILED(hr)) {
            return false;
        }
        CComBSTR name;
        hr = (*this)->get_UniqueName(&name);
        if (FAILED(hr)) {
            return false;
        }
        return name == rhsname;
    }
    bool  operator!=(TUNINGSPACETYPE& rhs) {
        return !operator==(rhs);
    }
    PQTuneRequest CreateTuneRequest() {
        PQTuneRequest p;
        HRESULT hr = (*this)->CreateTuneRequest(&p);
        if (FAILED(hr)) {
            return PQTuneRequest();
        }
        return p;
    }

    PQLocator Locator() {
        _ASSERT(*this);
        PQLocator ts;
        HRESULT hr = (*this)->get_DefaultLocator(&ts);
        if (FAILED(hr)) {
            return PQLocator();
        }
        return ts;
    }

    HRESULT Locator(PQLocator& l) {
        _ASSERT(*this);
        return (*this)->put_Locator(l);
    }

    void Clone() {
        PQTuningSpace t;
        HRESULT hr = (*this)->Clone(&t);
        if (FAILED(hr) || !t) {
            Release();  // clone failed, clear ourselves
            return;
        }
        TUNINGSPACETYPE::operator=(t);
    }

};

typedef TNTuningSpaceHelper<PQTuningSpace, PQTuneRequest> TNTuningSpace;

template<class TUNINGSPACETYPE, class TUNEREQUESTTYPE> class TNAnalogRadioTuningSpaceHelper : public TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> {
public:
     TNAnalogRadioTuningSpaceHelper() {}
     TNAnalogRadioTuningSpaceHelper(const TUNINGSPACETYPE &a) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
     TNAnalogRadioTuningSpaceHelper(IUnknown *p) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(p) {}
     TNAnalogRadioTuningSpaceHelper(const TNAnalogRadioTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> &a) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
     TNAnalogRadioTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNAnalogRadioTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
     }
     template<class TS, class TR> TNAnalogRadioTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNTuningSpaceHelper<TS, TR>& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(TUNINGSPACETYPE(rhs));
        return *this;
     }
     TNAnalogRadioTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TUNINGSPACETYPE& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
     TNAnalogRadioTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(IUnknown* rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    long MaxFrequency() {
        _ASSERT(*this);
        long freq;
        HRESULT hr = (*this)->get_MaxFrequency(&freq);
        if (FAILED(hr)) {
            freq = DEFAULT_MAX_FREQUENCY;
        }
        return freq;
    }
    HRESULT MaxFrequency(long freq) {
        _ASSERT(*this);
        return (*this)->put_MaxFrequency(freq);
    }
    long MinFrequency() {
        _ASSERT(*this);
        long freq;
        HRESULT hr = (*this)->get_MinFrequency(&freq);
        if (FAILED(hr)) {
            freq = DEFAULT_MIN_FREQUENCY;
        }
        return freq;
    }
    HRESULT MinFrequency(long freq) {
        _ASSERT(*this);
        return (*this)->put_MinFrequency(freq);
    }
};
typedef TNAnalogRadioTuningSpaceHelper<PQAnalogRadioTuningSpace, PQChannelTuneRequest> TNAnalogRadioTuningSpace;

template<class TUNINGSPACETYPE, class TUNEREQUESTTYPE> class TNAnalogTVTuningSpaceHelper : public TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> {
public:
    TNAnalogTVTuningSpaceHelper() {}
    TNAnalogTVTuningSpaceHelper(const TUNINGSPACETYPE &a) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
    TNAnalogTVTuningSpaceHelper(IUnknown *p) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(p) {}
    TNAnalogTVTuningSpaceHelper(const TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> &a) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
    TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    template<class TS, class TR> TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNTuningSpaceHelper<TS, TR>& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(TUNINGSPACETYPE(rhs));
        return *this;
    }
    TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TUNINGSPACETYPE& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(IUnknown* rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    TunerInputType InputType() {
        _ASSERT(*this);
        TunerInputType ti;
        HRESULT hr = (*this)->get_InputType(&ti);
        if (FAILED(hr)) {
            ti = DEFAULT_ANALOG_TUNER_INPUT_TYPE;
        }
        return ti;
    }
    HRESULT InputType(TunerInputType ti) {
        _ASSERT(*this);
        return (*this)->put_InputType(&ti);
    }
    long CountryCode() {
        _ASSERT(*this);
        long cc;
        HRESULT hr = (*this)->get_CountryCode(&cc);
        if (FAILED(hr)) {
            cc = DEFAULT_ANALOG_TUNER_INPUT_TYPE;
        }
        return cc;
    }
    HRESULT CountryCode(long cc) {
        _ASSERT(*this);
        return (*this)->put_CountryCode(cc);
    }
    long MinChannel() {
        _ASSERT(*this);
        long chan;
        HRESULT hr = (*this)->get_MinChannel(&chan);
        if (FAILED(hr)) {
            chan = DEFAULT_MIN_CHANNEL;
        }
        return chan;
    }
    HRESULT MinChannel(long chan) {
        _ASSERT(*this);
        return (*this)->put_MinChannel(chan);
    }
    long MaxChannel() {
        _ASSERT(*this);
        long chan;
        HRESULT hr = (*this)->get_MaxChannel(&chan);
        if (FAILED(hr)) {
            chan = DEFAULT_MAX_CHANNEL;
        }
        return chan;
    }
    HRESULT MaxChannel(long chan) {
        _ASSERT(*this);
        return (*this)->put_MaxChannel(chan);
    }
};
typedef TNAnalogTVTuningSpaceHelper<PQAnalogTVTuningSpace, PQChannelTuneRequest> TNAnalogTVTuningSpace;

template<class TUNINGSPACETYPE, class TUNEREQUESTTYPE> class TNAuxInTuningSpaceHelper : public TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> {
public:
    TNAuxInTuningSpaceHelper() {}
    TNAuxInTuningSpaceHelper(const TUNINGSPACETYPE &a) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
    TNAuxInTuningSpaceHelper(IUnknown *p) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(p) {}
    TNAuxInTuningSpaceHelper(const TNAuxInTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> &a) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
    TNAuxInTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNAuxInTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    template<class TS, class TR> TNAuxInTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNTuningSpaceHelper<TS, TR>& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(TUNINGSPACETYPE(rhs));
        return *this;
    }
    TNAuxInTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TUNINGSPACETYPE& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    TNAuxInTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(IUnknown* rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
};
typedef TNAuxInTuningSpaceHelper<PQAuxInTuningSpace, PQChannelTuneRequest> TNAuxInTuningSpace;

template<class TUNINGSPACETYPE, class TUNEREQUESTTYPE> class TNATSCTuningSpaceHelper : public TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> {
public:
    TNATSCTuningSpaceHelper() {}
    TNATSCTuningSpaceHelper(const TUNINGSPACETYPE &a) : TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
    TNATSCTuningSpaceHelper(IUnknown *p) : TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(p) {}
    TNATSCTuningSpaceHelper(const TNATSCTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> &a) : TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}

    TNATSCTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNATSCTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& rhs) {
        TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    template<class TS, class TR> TNATSCTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNTuningSpaceHelper<TS, TR>& rhs) {
        TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(TUNINGSPACETYPE(rhs));
        return *this;
    }
    TNATSCTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TUNINGSPACETYPE& rhs) {
        TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    TNATSCTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(IUnknown* rhs) {
        TNAnalogTVTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    long MinMinorChannel() {
        _ASSERT(*this);
        long chan;
        HRESULT hr = (*this)->get_MinMinorChannel(&chan);
        if (FAILED(hr)) {
            chan = DEFAULT_MIN_CHANNEL;
        }
        return chan;
    }
    HRESULT MinMinorChannel(long chan) {
        _ASSERT(*this);
        return (*this)->put_MinMinorChannel(chan);
    }

    long MaxMinorChannel() {
        _ASSERT(*this);
        long chan;
        HRESULT hr = (*this)->get_MaxMinorChannel(&chan);
        if (FAILED(hr)) {
            chan = DEFAULT_MAX_CHANNEL;
        }
        return chan;
    }
    HRESULT MaxMinorChannel(long chan) {
        _ASSERT(*this);
        return (*this)->put_MaxMinorChannel(chan);
    }
    long MinPhysicalChannel() {
        _ASSERT(*this);
        long chan;
        HRESULT hr = (*this)->get_MinPhysicalChannel(&chan);
        if (FAILED(hr)) {
            chan = DEFAULT_MIN_CHANNEL;
        }
        return chan;
    }
    HRESULT MinPhysicalChannel(long chan) {
        _ASSERT(*this);
        return (*this)->put_MinPhysicalChannel(chan);
    }

    long MaxPhysicalChannel() {
        _ASSERT(*this);
        long chan;
        HRESULT hr = (*this)->get_MaxPhysicalChannel(&chan);
        if (FAILED(hr)) {
            chan = DEFAULT_MAX_CHANNEL;
        }
        return chan;
    }

    HRESULT MaxPhysicalChannel(long chan) {
        _ASSERT(*this);
        return (*this)->put_MaxPhysicalChannel(chan);
    }
};
typedef TNATSCTuningSpaceHelper<PQATSCTuningSpace, PQATSCChannelTuneRequest> TNATSCTuningSpace;

// dvb tuning space
template<class TUNINGSPACETYPE, class TUNEREQUESTTYPE> class TNDVBTuningSpaceHelper : public TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> {
public:
     TNDVBTuningSpaceHelper() {}
     TNDVBTuningSpaceHelper(const TUNINGSPACETYPE &a) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
     TNDVBTuningSpaceHelper(IUnknown *p) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(p) {}
     TNDVBTuningSpaceHelper(const TNDVBTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE> &a) : TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>(a) {}
     TNDVBTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNDVBTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
     }
     template<class TS, class TR> TNDVBTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TNTuningSpaceHelper<TS, TR>& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(TUNINGSPACETYPE(rhs));
        return *this;
     }
     TNDVBTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(TUNINGSPACETYPE& rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
     TNDVBTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>& operator=(IUnknown* rhs) {
        TNTuningSpaceHelper<TUNINGSPACETYPE, TUNEREQUESTTYPE>::operator=(rhs);
        return *this;
    }
    DVBSystemType SystemType() const {
        DVBSystemType st;
        HRESULT hr = (*this)->get_SystemType(&st);
        if (FAILED(hr)) {
            return DVB_Cable;
        }
        return st;
    }
    HRESULT SystemType(DVBSystemType st) {
        _ASSERT(*this);
        return (*this)->put_SystemType(st);
    }
};
typedef TNDVBTuningSpaceHelper<PQDVBTuningSpace, PQDVBTuneRequest> TNDVBTuningSpace;

// locators
template<class LOCATORTYPE> class TNLocatorHelper : public LOCATORTYPE {
public:
     TNLocatorHelper() {}
     TNLocatorHelper(const LOCATORTYPE &a) : LOCATORTYPE(a) {}
     TNLocatorHelper(IUnknown *p) : LOCATORTYPE(p) {}
     TNLocatorHelper(const TNLocatorHelper<LOCATORTYPE> &a) : LOCATORTYPE(a) {}
     TNLocatorHelper(ILocator *p) : LOCATORTYPE(p) {}
     TNLocatorHelper<LOCATORTYPE>& operator=(TNLocatorHelper<LOCATORTYPE>& rhs) {
        LOCATORTYPE::operator=(rhs);
        return *this;
    }
     TNLocatorHelper<LOCATORTYPE>& operator=(LOCATORTYPE& rhs) {
        LOCATORTYPE::operator=(rhs);
        return *this;
    }
     TNLocatorHelper<LOCATORTYPE>& operator=(ILocator* rhs) {
        LOCATORTYPE::operator=(rhs);
        return *this;
    }
     TNLocatorHelper<LOCATORTYPE>& operator=(IUnknown* rhs) {
        LOCATORTYPE::operator=(rhs);
        return *this;
    }

    void Clone() {
        PQLocator t;
        HRESULT hr = (*this)->Clone(&t);
        if (FAILED(hr) || !t) {
            Release();  // clone failed, clear ourselves
            return;
        }
        LOCATORTYPE::operator=(t);
    }

    long CarrierFrequency() {
        _ASSERT(*this);
        long f;
        HRESULT hr = (*this)->get_CarrierFrequency(&f);
        if (FAILED(hr)) {
            return -1;
        }
        return f;
    }
    HRESULT CarrierFrequency(long f) {
        _ASSERT(*this);
        return (*this)->put_CarrierFrequency(f);
    }

    FECMethod InnerFEC() {
        _ASSERT(*this);
        FECMethod f;
        HRESULT hr = (*this)->get_InnerFEC(&f);
        if (FAILED(hr)) {
            return BDA_FEC_METHOD_NOT_SET;
        }
        return f;
    }
    HRESULT InnerFEC(FECMethod f) {
        _ASSERT(*this);
        return (*this)->put_InnerFEC(f);
    }
    BinaryConvolutionCodeRate InnerFECRate() {
        _ASSERT(*this);
        BinaryConvolutionCodeRate f;
        HRESULT hr = (*this)->get_InnerFECRate(&f);
        if (FAILED(hr)) {
            return BDA_BCC_RATE_NOT_SET;
        }
        return f;
    }
    HRESULT InnerFECRate(BinaryConvolutionCodeRate f) {
        _ASSERT(*this);
        return (*this)->put_InnerFECRate(f);
    }
    FECMethod OuterFEC() {
        _ASSERT(*this);
        FECMethod f;
        HRESULT hr = (*this)->get_OuterFEC(&f);
        if (FAILED(hr)) {
            return BDA_FEC_METHOD_NOT_SET;
        }
        return f;
    }
    HRESULT OuterFEC(FECMethod f) {
        _ASSERT(*this);
        return (*this)->put_OuterFEC(f);
    }
    BinaryConvolutionCodeRate OuterFECRate() {
        _ASSERT(*this);
        BinaryConvolutionCodeRate f;
        HRESULT hr = (*this)->get_OuterFECRate(&f);
        if (FAILED(hr)) {
            return BDA_BCC_RATE_NOT_SET;
        }
        return f;
    }
    HRESULT OuterFECRate(BinaryConvolutionCodeRate f) {
        _ASSERT(*this);
        return (*this)->put_OuterFECRate(f);
    }
    ModulationType Modulation() {
        _ASSERT(*this);
        ModulationType f;
        HRESULT hr = (*this)->get_Modulation(&f);
        if (FAILED(hr)) {
            return BDA_MOD_NOT_SET;
        }
        return f;
    }
    HRESULT Modulation(ModulationType f) {
        _ASSERT(*this);
        return (*this)->put_Modulation(f);
    }

    long SymbolRate() {
        _ASSERT(*this);
        long f;
        HRESULT hr = (*this)->get_SymbolRate(&f);
        if (FAILED(hr)) {
            return -1;
        }
        return f;
    }
    HRESULT SymbolRate(long f) {
        _ASSERT(*this);
        return (*this)->put_SymbolRate(f);
    }

};
typedef TNLocatorHelper<PQLocator> TNLocator;

template<class LOCATORTYPE> class TNATSCLocatorHelper : public TNLocatorHelper<LOCATORTYPE> {
public:
    TNATSCLocatorHelper() {}
    TNATSCLocatorHelper(const LOCATORTYPE &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNATSCLocatorHelper(IUnknown *p) : TNLocatorHelper<LOCATORTYPE>(p) {}
    TNATSCLocatorHelper(const TNATSCLocatorHelper<LOCATORTYPE> &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNATSCLocatorHelper(IATSCLocator *p) : TNLocatorHelper<LOCATORTYPE>(p) {}
    TNATSCLocatorHelper(const TNLocatorHelper<LOCATORTYPE> &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNATSCLocatorHelper<LOCATORTYPE>& operator=(TNATSCLocatorHelper<LOCATORTYPE>& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNATSCLocatorHelper<LOCATORTYPE>& operator=(TNLocatorHelper<LOCATORTYPE>& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNATSCLocatorHelper<LOCATORTYPE>& operator=(LOCATORTYPE& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNATSCLocatorHelper<LOCATORTYPE>& operator=(IATSCLocator* rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNATSCLocatorHelper<LOCATORTYPE>& operator=(IUnknown* rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }

    long PhysicalChannel() {
        _ASSERT(*this);
        long pc;
        HRESULT hr = (*this)->get_PhysicalChannel(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT PhysicalChannel(long pc) {
        _ASSERT(*this);
        return (*this)->put_PhysicalChannel(pc);
    }

    long TSID() {
        _ASSERT(*this);
        long pc;
        HRESULT hr = (*this)->get_TSID(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT TSID(long pc) {
        _ASSERT(*this);
        return (*this)->put_TSID(pc);
    }

    long ProgramNumber() {
        _ASSERT(*this);
        long pc;
        HRESULT hr = (*this)->get_ProgramNumber(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT ProgramNumber(long pc) {
        _ASSERT(*this);
        return (*this)->put_ProgramNumber(pc);
    }
};
typedef TNATSCLocatorHelper<PQATSCLocator> TNATSCLocator;

template<class LOCATORTYPE> class TNDVBSLocatorHelper : public TNLocatorHelper<LOCATORTYPE> {
public:
    TNDVBSLocatorHelper() {}
    TNDVBSLocatorHelper(const LOCATORTYPE &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBSLocatorHelper(IUnknown *p) : TNLocatorHelper<LOCATORTYPE>(p) {}
    TNDVBSLocatorHelper(const TNDVBSLocatorHelper<LOCATORTYPE> &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBSLocatorHelper(IDVBSLocator *p) : TNLocatorHelper<LOCATORTYPE>(p) {}
    TNDVBSLocatorHelper(const TNLocatorHelper<LOCATORTYPE> &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBSLocatorHelper<LOCATORTYPE>& operator=(TNDVBSLocatorHelper<LOCATORTYPE>& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBSLocatorHelper<LOCATORTYPE>& operator=(TNLocatorHelper<LOCATORTYPE>& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBSLocatorHelper<LOCATORTYPE>& operator=(LOCATORTYPE& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBSLocatorHelper<LOCATORTYPE>& operator=(IDVBSLocator* rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBSLocatorHelper<LOCATORTYPE>& operator=(IUnknown* rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }

    Polarisation SignalPolarisation() {
        _ASSERT(*this);
        Polarisation pc;
        HRESULT hr = (*this)->get_SignalPolarisation(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT SignalPolarisation(Polarisation pc) {
        _ASSERT(*this);
        return (*this)->put_SignalPolarisation(pc);
    }

    VARIANT_BOOL WestPosition() {
        _ASSERT(*this);
        VARIANT_BOOL pc;
        HRESULT hr = (*this)->get_WestPosition(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT WestPosition(VARIANT_BOOL pc) {
        _ASSERT(*this);
        return (*this)->put_WestPosition(pc);
    }

    long OrbitalPosition() {
        _ASSERT(*this);
        long pc;
        HRESULT hr = (*this)->get_OrbitalPosition(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT OrbitalPosition(long pc) {
        _ASSERT(*this);
        return (*this)->put_OrbitalPosition(pc);
    }

    long Azimuth() {
        _ASSERT(*this);
        long pc;
        HRESULT hr = (*this)->get_Azimuth(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT Azimuth(long pc) {
        _ASSERT(*this);
        return (*this)->put_Azimuth(pc);
    }

    long Elevation() {
        _ASSERT(*this);
        long pc;
        HRESULT hr = (*this)->get_Elevation(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT Elevation(long pc) {
        _ASSERT(*this);
        return (*this)->put_Elevation(pc);
    }

};
typedef TNDVBSLocatorHelper<PQDVBSLocator> TNDVBSLocator;



template<class LOCATORTYPE> class TNDVBTLocatorHelper : public TNLocatorHelper<LOCATORTYPE> {
public:
    TNDVBTLocatorHelper() {}
    TNDVBTLocatorHelper(const LOCATORTYPE &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBTLocatorHelper(IUnknown *p) : TNLocatorHelper<LOCATORTYPE>(p) {}
    TNDVBTLocatorHelper(const TNDVBTLocatorHelper<LOCATORTYPE> &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBTLocatorHelper(IDVBTLocator *p) : TNLocatorHelper<LOCATORTYPE>(p) {}
    TNDVBTLocatorHelper(const TNLocatorHelper<LOCATORTYPE> &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBTLocatorHelper<LOCATORTYPE>& operator=(TNDVBTLocatorHelper<LOCATORTYPE>& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBTLocatorHelper<LOCATORTYPE>& operator=(TNLocatorHelper<LOCATORTYPE>& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBTLocatorHelper<LOCATORTYPE>& operator=(LOCATORTYPE& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBTLocatorHelper<LOCATORTYPE>& operator=(IDVBTLocator* rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBTLocatorHelper<LOCATORTYPE>& operator=(IUnknown* rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }

    long BandWidth() {
        _ASSERT(*this);
        long pc;
        HRESULT hr = (*this)->get_BandWidth(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT BandWidth(long pc) {
        _ASSERT(*this);
        return (*this)->put_BandWidth(pc);
    }

    FECMethod LPInnerFec() {
        _ASSERT(*this);
        FECMethod pc;
        HRESULT hr = (*this)->get_LPInnerFec(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT LPInnerFec(FECMethod pc) {
        _ASSERT(*this);
        return (*this)->put_LPInnerFec(pc);
    }

    BinaryConvolutionCodeRate LPInnerFecRate() {
        _ASSERT(*this);
        BinaryConvolutionCodeRate pc;
        HRESULT hr = (*this)->get_LPInnerFecRate(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT LPInnerFecRate(BinaryConvolutionCodeRate pc) {
        _ASSERT(*this);
        return (*this)->put_LPInnerFecRate(pc);
    }

    HierarchyAlpha HAlpha() {
        _ASSERT(*this);
        HierarchyAlpha pc;
        HRESULT hr = (*this)->get_HAlpha(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT HAlpha(HierarchyAlpha pc) {
        _ASSERT(*this);
        return (*this)->put_HAlpha(pc);
    }

    GuardInterval Guard() {
        _ASSERT(*this);
        GuardInterval pc;
        HRESULT hr = (*this)->get_Guard(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT Guard(GuardInterval pc) {
        _ASSERT(*this);
        return (*this)->put_Guard(pc);
    }

    TransmissionMode Mode() {
        _ASSERT(*this);
        TransmissionMode pc;
        HRESULT hr = (*this)->get_Mode(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT Mode(TransmissionMode pc) {
        _ASSERT(*this);
        return (*this)->put_Mode(pc);
    }

    VARIANT_BOOL OtherFrequencyInUse() {
        _ASSERT(*this);
        VARIANT_BOOL pc;
        HRESULT hr = (*this)->get_OtherFrequencyInUse(&pc);
        if (FAILED(hr)) {
            return -1;
        }
        return pc;
    }
    HRESULT OtherFrequencyInUse(VARIANT_BOOL pc) {
        _ASSERT(*this);
        return (*this)->put_OtherFrequencyInUse(pc);
    }
};
typedef TNDVBTLocatorHelper<PQDVBTLocator> TNDVBTLocator;

template<class LOCATORTYPE> class TNDVBCLocatorHelper : public TNLocatorHelper<LOCATORTYPE> {
public:
    TNDVBCLocatorHelper() {}
    TNDVBCLocatorHelper(const LOCATORTYPE &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBCLocatorHelper(IUnknown *p) : TNLocatorHelper<LOCATORTYPE>(p) {}
    TNDVBCLocatorHelper(const TNDVBCLocatorHelper<LOCATORTYPE> &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBCLocatorHelper(IDVBCLocator *p) : TNLocatorHelper<LOCATORTYPE>(p) {}
    TNDVBCLocatorHelper(const TNLocatorHelper<LOCATORTYPE> &a) : TNLocatorHelper<LOCATORTYPE>(a) {}
    TNDVBCLocatorHelper<LOCATORTYPE>& operator=(TNDVBCLocatorHelper<LOCATORTYPE>& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBCLocatorHelper<LOCATORTYPE>& operator=(TNLocatorHelper<LOCATORTYPE>& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBCLocatorHelper<LOCATORTYPE>& operator=(LOCATORTYPE& rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBCLocatorHelper<LOCATORTYPE>& operator=(IDVBCLocator* rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNDVBCLocatorHelper<LOCATORTYPE>& operator=(IUnknown* rhs) {
        TNLocatorHelper<LOCATORTYPE>::operator=(rhs);
        return *this;
    }

};
typedef TNDVBCLocatorHelper<PQDVBCLocator> TNDVBCLocator;

// tune requests
template<class TUNEREQUESTTYPE, class LOCATORTYPE> class TNTuneRequestHelper : public TUNEREQUESTTYPE {
public:
     TNTuneRequestHelper() {}
     TNTuneRequestHelper(const TUNEREQUESTTYPE &a) : TUNEREQUESTTYPE(a) {}
     TNTuneRequestHelper(IUnknown *p) : TUNEREQUESTTYPE(p) {}
     TNTuneRequestHelper(const TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> &a) : TUNEREQUESTTYPE(a) {}
     TNTuneRequestHelper(ITuneRequest *p) : TUNEREQUESTTYPE(p) {}
     TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& rhs) {
        TUNEREQUESTTYPE::operator=(rhs);
        return *this;
    }
     TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TUNEREQUESTTYPE& rhs) {
        TUNEREQUESTTYPE::operator=(rhs);
        return *this;
    }
     TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(ITuneRequest* rhs) {
        TUNEREQUESTTYPE::operator=(rhs);
        return *this;
    }
     TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(IUnknown* rhs) {
        TUNEREQUESTTYPE::operator=(rhs);
        return *this;
    }
    // this function creates a new instance of the base ITuneRequest* and copies
    // all the values of the current ITuneRequest and sets this to the new one
    // this provides the value semantics needed by the network providers
    void Clone() {
        PQTuneRequest t;
        HRESULT hr = (*this)->Clone(&t);
        if (FAILED(hr) || !t) {
            Release();  // clone failed, clear ourselves
            return;
        }
        TUNEREQUESTTYPE::operator=(t);
    }

    PQTuningSpace TuningSpace() {
        _ASSERT(*this);
        PQTuningSpace ts;
        HRESULT hr = (*this)->get_TuningSpace(&ts);
        if (FAILED(hr)) {
            return PQTuningSpace();
        }
        return ts;
    }

    LOCATORTYPE Locator() {
        _ASSERT(*this);
        PQLocator pc;
        HRESULT hr = (*this)->get_Locator(&pc);
        if (FAILED(hr)) {
            return PQLocator().p;
        }
        return pc.p;
    }
    HRESULT Locator(LOCATORTYPE& pc) {
        _ASSERT(*this);
        return (*this)->put_Locator(pc);
    }
};

typedef TNTuneRequestHelper<PQTuneRequest, PQLocator> TNTuneRequest;

template<class TUNEREQUESTTYPE, class LOCATORTYPE> class TNChannelTuneRequestHelper : public TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> {
public:
     TNChannelTuneRequestHelper() {}
     TNChannelTuneRequestHelper(const TNTuneRequest &a) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
     TNChannelTuneRequestHelper(IChannelTuneRequest *p) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(p) {}
     TNChannelTuneRequestHelper(IUnknown *p) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(p) {}
     TNChannelTuneRequestHelper(const TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> &a) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
     TNChannelTuneRequestHelper(const TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> &a) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
     TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& rhs) {
        TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    template<class TR, class LOC> TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TNTuneRequestHelper<TR, LOC>& rhs) {
        TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(TUNEREQUESTTYPE(rhs));
        return *this;
    }
     TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TUNEREQUESTTYPE& rhs) {
        TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
     TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(IChannelTuneRequest* rhs) {
        TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
     TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(IUnknown* rhs) {
        TUNEREQUESTTYPE::operator=(rhs);
        return *this;
    }
    long Channel() {
        _ASSERT(*this);
        long c;
        HRESULT hr = (*this)->get_Channel(&c);
        if (FAILED(hr)) {
            return -1;
        }
        return c;
    }
    HRESULT Channel(long c) {
        _ASSERT(*this);
        return (*this)->put_Channel(c);
    }
};

typedef TNChannelTuneRequestHelper<PQChannelTuneRequest, PQLocator> TNChannelTuneRequest;

template<class TUNEREQUESTTYPE, class LOCATORTYPE> class TNATSCChannelTuneRequestHelper : public TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> {
public:
    TNATSCChannelTuneRequestHelper() {}
    TNATSCChannelTuneRequestHelper(const TNTuneRequest &a) : TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
    TNATSCChannelTuneRequestHelper(IATSCChannelTuneRequest *p) : TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(p) {}
    TNATSCChannelTuneRequestHelper(IUnknown *p) : TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(p) {}
    TNATSCChannelTuneRequestHelper(const TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> &a) : TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
    TNATSCChannelTuneRequestHelper(const TNATSCChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> &a) : TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
    TNATSCChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TNATSCChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& rhs) {
        TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    template<class TR, class LOC>TNATSCChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TNTuneRequestHelper<TR, LOC>& rhs) {
        TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(TR(rhs));
        return *this;
    }
    TNATSCChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TUNEREQUESTTYPE& rhs) {
        TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNATSCChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(IATSCChannelTuneRequest *rhs) {
        TNChannelTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(IUnknown* rhs) {
        TUNEREQUESTTYPE::operator=(rhs);
        return *this;
    }
    long MinorChannel() {
        _ASSERT(*this);
        long mc;
        HRESULT hr = (*this)->get_MinorChannel(&mc);
        if (FAILED(hr)) {
            return -1;
        }
        return mc;
    }
    HRESULT MinorChannel(long mc) {
        _ASSERT(*this);
        return (*this)->put_MinorChannel(mc);
    }
};
typedef TNATSCChannelTuneRequestHelper<PQATSCChannelTuneRequest, PQATSCLocator> TNATSCChannelTuneRequest;

template<class TUNEREQUESTTYPE, class LOCATORTYPE> class TNDVBTuneRequestHelper : public TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> {
public:
     TNDVBTuneRequestHelper() {}
     TNDVBTuneRequestHelper(const TNTuneRequest &a) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
     TNDVBTuneRequestHelper(IDVBTuneRequest *p) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(p) {}
     TNDVBTuneRequestHelper(IUnknown *p) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(p) {}
     TNDVBTuneRequestHelper(const TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> &a) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
     TNDVBTuneRequestHelper(const TNDVBTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE> &a) : TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>(a) {}
     TNDVBTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TNDVBTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& rhs) {
        TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
    template<class TR, class LOC> TNDVBTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TNTuneRequestHelper<TR, LOC>& rhs) {
        TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(TUNEREQUESTTYPE(rhs));
        return *this;
    }
     TNDVBTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(TUNEREQUESTTYPE& rhs) {
        TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
     TNDVBTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(IDVBTuneRequest* rhs) {
        TNTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>::operator=(rhs);
        return *this;
    }
     TNDVBTuneRequestHelper<TUNEREQUESTTYPE, LOCATORTYPE>& operator=(IUnknown* rhs) {
        TUNEREQUESTTYPE::operator=(rhs);
        return *this;
    }
    long ONID() {
        _ASSERT(*this);
        long c;
        HRESULT hr = (*this)->get_ONID(&c);
        if (FAILED(hr)) {
            return -1;
        }
        return c;
    }
    HRESULT ONID(long c) {
        _ASSERT(*this);
        return (*this)->put_ONID(c);
    }
    long TSID() {
        _ASSERT(*this);
        long c;
        HRESULT hr = (*this)->get_TSID(&c);
        if (FAILED(hr)) {
            return -1;
        }
        return c;
    }
    HRESULT TSID(long c) {
        _ASSERT(*this);
        return (*this)->put_TSID(c);
    }
    long SID() {
        _ASSERT(*this);
        long c;
        HRESULT hr = (*this)->get_SID(&c);
        if (FAILED(hr)) {
            return -1;
        }
        return c;
    }
    HRESULT SID(long c) {
        _ASSERT(*this);
        return (*this)->put_SID(c);
    }
};
typedef TNDVBTuneRequestHelper<PQDVBTuneRequest, PQLocator> TNDVBTuneRequest;
}; // namespace

#ifndef NO_DEFAULT_BDATUNINGMODEL_NAMESPACE
using namespace BDATuningModel;
#endif

#endif
// end of file - tune.h
