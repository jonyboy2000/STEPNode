// $RCSfile: $
// $Revision: $ $Date: $
// Auth: Samson Bonfante (bonfante@steptools.com)
//
// Copyright (c) 1991-2016 by STEP Tools Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "nodeTolerance.h"
#include "nodeUtils.h"

Tolerance * Tolerance::_singleton = nullptr;
NAN_METHOD(Tolerance::New)
{
    if (info.IsConstructCall())
    {
	if (!info[0]->IsUndefined())
	{
	    return;
	}
	if (_singleton == nullptr)
	    _singleton = new Tolerance();
	_singleton->Wrap(info.This());
	info.GetReturnValue().Set(info.This());
    }
    else
    {
	return;
    }
}

NAN_MODULE_INIT(Tolerance::Init)
{
    v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("Tolerance").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    Nan::SetPrototypeMethod(tpl, "GetToleranceAllCount", GetToleranceAllCount);
    Nan::SetPrototypeMethod(tpl, "GetToleranceAllNext", GetToleranceAllNext);

    constructor().Reset(Nan::GetFunction(tpl).ToLocalChecked());
    Nan::Set(target, Nan::New("Tolerance").ToLocalChecked(), Nan::GetFunction(tpl).ToLocalChecked());

}

NAN_METHOD(Tolerance::GetToleranceAllCount)
{
  Tolerance* tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
  if(!tol)
    return;
  if(info.Length!=0)
    return;
  int size = 0;
  if(!tol->_tol->tolerance_count(size))
    return;
  info.GetReturnValue().Set(size);
  return;
}

NAN_METHOD(Tolerance::GetToleranceAllNext)
{
  Tolerance* tol = Nan::ObjectWrap::Unwrap<Tolerance>(info.This());
  if(!tol)
    return;
  if(info.Length!=1)
    return;
  if(!info[0]->IsNumber())
    return;
  int index = (int)info[0];
  int tol_id = 0;
  if (!tol->_tol->tolerance_next(index, tol_id))
    return;
  info.GetReturnValue().Set(tol_id);
  return;
}
