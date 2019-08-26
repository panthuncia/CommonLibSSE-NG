#include "RE/FxDelegate.h"

#include "RE/AddCallbackVisitor.h"  // AddCallbackVisitor
#include "RE/FxDelegateArgs.h"  // FxDelegateArgs
#include "RE/FxResponseArgsBase.h"  // FxResponseArgsBase
#include "RE/GFxMovieView.h"  // GFxMovieView
#include "RE/GFxValue.h"  // GFxValue
#include "RE/RemoveCallbackVisitor.h"  // RemoveCallbackVisitor


namespace RE
{
	UPInt FxDelegate::CallbackHashFunctor::operator()(const GString& a_data) const
	{
		return GString::BernsteinHashFunction(a_data.c_str(), a_data.length());
	}


	void FxDelegate::Callback(GFxMovieView* a_movieView, const char* a_methodName, const GFxValue* a_args, UInt32 a_argCount)
	{
		auto cbDef = callbacks.GetAlt(a_methodName);
		if (cbDef) {
			FxDelegateArgs params(GFxValue(), cbDef->handler.get(), a_movieView, a_args, a_argCount);
			cbDef->callback(params);
		}
	}


	void FxDelegate::Invoke(GFxMovieView* a_movieView, const char* a_methodName, FxResponseArgsBase& a_args)
	{
		GFxValue* values = 0;
		UInt32 numValues = a_args.GetValues(&values);
		values[0] = a_methodName;
		a_movieView->InvokeNoReturn("call", values, numValues);
	}


	void FxDelegate::Invoke2(GFxMovieView* a_movieView, const char* a_methodName, FxResponseArgsBase& a_args)
	{
		GFxValue* values = 0;
		UInt32 numValues = a_args.GetValues(&values);
		a_movieView->Invoke(a_methodName, 0, values + 1, numValues - 1);
	}


	void FxDelegate::RegisterHandler(FxDelegateHandler* a_callback)
	{
		AddCallbackVisitor reg(a_callback, &callbacks);
		a_callback->Accept(&reg);
	}


	void FxDelegate::UnregisterHandler(FxDelegateHandler* a_callback)
	{
		RemoveCallbackVisitor reg(&callbacks);
		a_callback->Accept(&reg);
	}
}