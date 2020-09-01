//----------------------------------------------------------------------------
// Copyright 2020, Ed Keenan, all rights reserved.
//----------------------------------------------------------------------------

#ifndef _VOICE_CALLBACK_H_
#define _VOICE_CALLBACK_H_

#include "XAudio2Wrapper.h"
#include "ASnd.h"

//  Sample voice callback
class VoiceCallback : public IXAudio2VoiceCallback
{
public:
	VoiceCallback(const VoiceCallback &) = delete;
	VoiceCallback(VoiceCallback&&) = delete;
	VoiceCallback& operator = (const VoiceCallback&) = delete;
	VoiceCallback& operator = (VoiceCallback&&) = delete;

	VoiceCallback();
	virtual ~VoiceCallback();

	void SetASnd(ASnd* _pASnd);
	ASnd* GetASnd();

	void SetNextSnd();

	void STDMETHODCALLTYPE OnStreamEnd() noexcept override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassEnd() noexcept override;
	void STDMETHODCALLTYPE OnVoiceProcessingPassStart(UINT32) noexcept override;
	void STDMETHODCALLTYPE OnBufferEnd(void*) noexcept override;
	void STDMETHODCALLTYPE OnBufferStart(void*) noexcept override;
	void STDMETHODCALLTYPE OnLoopEnd(void*) noexcept override;
	void STDMETHODCALLTYPE OnVoiceError(void*, HRESULT) noexcept override;

	// Data: 
	ASnd* pASnd;
	ASnd* pNextSnd;
};

#endif

// End of File 
