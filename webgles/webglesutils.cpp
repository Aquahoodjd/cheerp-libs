/****************************************************************
 *
 * Copyright (C) 2013 Alessandro Pignotti <alessandro@leaningtech.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 *
 ***************************************************************/

#include "webgles.h"
#include <duettointrin.h>

client::WebGLRenderingContext* webGLES;

void webGLESInit(const client::String& canvasName)
{
	webGLESLookupArrayInit();
	auto canvas = static_cast<client::HTMLCanvasElement*>(client::document.getElementById(canvasName));
	webGLES = reinterpret_cast<client::WebGLRenderingContext*>(canvas->getContext("experimental-webgl"));
	if (webGLES == NULL)
		client::window.alert("Sorry, we looked hard, but no sign of WebGL has been found :(");
}

client::ArrayBufferView* BufferForPointer(const void* ptr)
{
	size_t offset=__builtin_duetto_pointer_offset(ptr);
	//Use an Int8Array as the fake type, it does not matter anyway
	client::Int8Array* buf=(client::Int8Array*)__builtin_duetto_pointer_base(ptr);
	if(offset==0)
		return buf;
	else
		return buf->subarray(offset);
}

client::ArrayBufferView* BufferForPointer(const void* ptr, unsigned int size)
{
	size_t offset=__builtin_duetto_pointer_offset(ptr);
	//Use an Int8Array as the fake type, the actual data type is described by the BYTES_PER_ELEMENT attribute
	client::Int8Array* buf=(client::Int8Array*)__builtin_duetto_pointer_base(ptr);
	return buf->subarray(offset, size/buf->get_BYTES_PER_ELEMENT());
}
