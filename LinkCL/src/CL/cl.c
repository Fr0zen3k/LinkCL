#include "Core/Core.h"
#include "cl.h"

#ifdef LINKCL_WINDOWS
#include <Windows.h>
#else
#include <dlfcn.h>
#endif


#ifdef LINKCL_ANDROID

#define LoadFunction(function)													\
	if(wrapper) {																\
		function = (f_##function)(LoadOpenCLPointer(#function));				\
	} else {																	\
		function = (f_##function)(dlsym(libopencl, #function));					\
	}			

#elif defined(LINKCL_WINDOWS)

#define LoadFunction(function)													\
	function = (f_##function)(GetProccAddress(libopencl, #function));			

#else

#define LoadFunction(function)													\
	function = (f_##function)(dlsym(libopencl, #function));				

#endif


#ifdef LINKCL_WINDOWS

void LoadOpenCLFunctions(HMODULE libopencl);

#else

void LoadOpenCLFunctions(void* libopencl, int wrapper);

#endif


int LoadOpenCL(int platformType) {

#ifdef LINKCL_WINDOWS

	HMODULE libopencl = LoadLibraryA("OpenCL.dll");

	if (libopencl) {
		LoadOpenCLFunctions(libopencl);
		return LINKCL_LINK_SUCCESS;
	} 
	else {
		return LINKCL_LINK_FAILURE;
	}

#endif

#ifdef LINKCL_MACOS

	void* libopencl = nullptr;

	libopencl = dlopen("/System/Library/Frameworks/OpenCL.framework/OpenCL", RTLD_NOW | RTLD_LOCAL);

	if(libopencl) {
		LoadOpenCLFunctions(libopencl, LINKCL_NORMAL);
		return LINKCL_LINK_SUCCESS;
	}
	else {
		return LINKCL_LINK_FAILURE;
	}

#endif

#ifdef LINKCL_LINUX

	void* libopencl = nullptr;

	libopencl = dlopen("libOpenCL.so", RTLD_NOW | RTLD_LOCAL);

	if (libopencl) {
		LoadOpenCLFunctions(libopencl, LINKCL_NORMAL);
		return LINKCL_LINK_SUCCESS;
	} 
	else {
		return LINKCL_LINK_FAILURE;
	}

#endif

#ifdef LINKCL_ANDROID

	void* libopencl = nullptr;

	libopencl = dlopen("libOpenCL-pixel.so", RTLD_NOW | RTLD_LOCAL);

	if (!libopencl) {
		libopencl = dlopen("libOpenCL-car.so", RTLD_NOW | RTLD_LOCAL);
	}

	if (libopencl) {
		typedef void (*f_enableOpenCL)();

		f_enableOpenCL enableOpenCL = (f_enableOpenCL)(dlsym(libopencl, "enableOpenCL"));
		enableOpenCL();

		LoadOpenCLFunctions(libopencl, LINKCL_WRAPPER);
		
		return LINKCL_LINK_SUCCESS;
	}
	else {
		libopencl = dlopen("libOpenCL.so", RTLD_NOW | RTLD_LOCAL);

		if (libopencl) {
			LoadOpenCLFunctions(libopencl, LINKCL_NORMAL);
			return LINKCL_LINK_SUCCESS;
		}
		else {
			return LINKCL_LINK_FAILURE;
		}
	}

#endif

}


#ifdef LINKCL_WINDOWS
void LoadOpenCLFunctions(HMODULE libopencl) {
#else
void LoadOpenCLFunctions(void* libopencl, int wrapper) {
#endif

#ifdef LINKCL_ANDROID
	if (wrapper) {
		typedef void* (*f_LoadOpenCLPointer)(const char* name);
		f_LoadOpenCLPointer LoadOpenCLPointer = dlsym(libopencl, "loadOpenCLPointer");
	}
#endif

#ifdef CL_VERSION_1_0
	LoadFunction(clGetPlatformIDs);
	LoadFunction(clGetPlatformInfo);
	LoadFunction(clGetDeviceIDs);
	LoadFunction(clGetDeviceInfo);
	LoadFunction(clCreateContext);
	LoadFunction(clCreateContextFromType);
	LoadFunction(clRetainContext);
	LoadFunction(clReleaseContext);
	LoadFunction(clGetContextInfo);
	LoadFunction(clRetainCommandQueue);
	LoadFunction(clReleaseCommandQueue);
	LoadFunction(clGetCommandQueueInfo);
	LoadFunction(clCreateBuffer);
	LoadFunction(clRetainMemObject);
	LoadFunction(clReleaseMemObject);
	LoadFunction(clGetSupportedImageFormats);
	LoadFunction(clGetMemObjectInfo);
	LoadFunction(clGetImageInfo);
	LoadFunction(clRetainSampler);
	LoadFunction(clReleaseSampler);
	LoadFunction(clGetSamplerInfo);
	LoadFunction(clCreateProgramWithSource);
	LoadFunction(clCreateProgramWithBinary);
	LoadFunction(clRetainProgram);
	LoadFunction(clReleaseProgram);
	LoadFunction(clBuildProgram);
	LoadFunction(clGetProgramInfo);
	LoadFunction(clGetProgramBuildInfo);
	LoadFunction(clCreateKernel);
	LoadFunction(clCreateKernelsInProgram);
	LoadFunction(clRetainKernel);
	LoadFunction(clReleaseKernel);
	LoadFunction(clSetKernelArg);
	LoadFunction(clGetKernelInfo);
	LoadFunction(clGetKernelWorkGroupInfo);
	LoadFunction(clWaitForEvents);
	LoadFunction(clGetEventInfo);
	LoadFunction(clRetainEvent);
	LoadFunction(clReleaseEvent);
	LoadFunction(clGetEventProfilingInfo);
	LoadFunction(clFlush);
	LoadFunction(clFinish);
	LoadFunction(clEnqueueReadBuffer);
	LoadFunction(clEnqueueWriteBuffer);
	LoadFunction(clEnqueueCopyBuffer);
	LoadFunction(clEnqueueReadImage);
	LoadFunction(clEnqueueWriteImage);
	LoadFunction(clEnqueueCopyImage);
	LoadFunction(clEnqueueCopyImageToBuffer);
	LoadFunction(clEnqueueCopyBufferToImage);
	LoadFunction(clEnqueueMapBuffer);
	LoadFunction(clEnqueueMapImage);
	LoadFunction(clEnqueueUnmapMemObject);
	LoadFunction(clEnqueueNDRangeKernel);
	LoadFunction(clEnqueueNativeKernel);
#ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
	LoadFunction(clSetCommandQueueProperty);
#endif
#endif

#ifdef CL_VERSION_1_1
	LoadFunction(clCreateSubBuffer);
	LoadFunction(clSetMemObjectDestructorCallback);
	LoadFunction(clCreateUserEvent);
	LoadFunction(clSetUserEventStatus);
	LoadFunction(clSetEventCallback);
	LoadFunction(clEnqueueReadBufferRect);
	LoadFunction(clEnqueueWriteBufferRect);
	LoadFunction(clEnqueueCopyBufferRect);
#ifdef CL_USE_DEPRECATED_OPENCL_1_1_APIS
	LoadFunction(clCreateImage2D);
	LoadFunction(clCreateImage3D);
	LoadFunction(clEnqueueMarker);
	LoadFunction(clEnqueueWaitForEvents);
	LoadFunction(clEnqueueBarrier);
	LoadFunction(clUnloadCompiler);
	LoadFunction(clGetExtensionFunctionAddress);
#endif
#endif

#ifdef CL_VERSION_1_2
	LoadFunction(clCreateSubDevices);
	LoadFunction(clRetainDevice);
	LoadFunction(clReleaseDevices);
	LoadFunction(clCreateImage);
	LoadFunction(clCreateProgramWithBuiltInKernels);
	LoadFunction(clCompileProgram);
	LoadFunction(clLinkProgram);
	LoadFunction(clUnloadPlatformCompiler);
	LoadFunction(clGetKernelArgInfo);
	LoadFunction(clEnqueueFillBuffer);
	LoadFunction(clEnqueueFillImage);
	LoadFunction(clEnqueueMigrateMemObjects);
	LoadFunction(clEnqueueMarkerWithWaitList);
	LoadFunction(clEnqueueBarrierWithWaitList);
	LoadFunction(clGetExtensionFunctionAddressForPlatform);
#endif

#ifdef CL_VERSION_2_0
	LoadFunction(clCreateCommandQueueWithProperties);
	LoadFunction(clCreatePipe);
	LoadFunction(clGetPipeInfo);
	LoadFunction(clSVMAlloc);
	LoadFunction(clSVMFree);
	LoadFunction(clCreateSamplerWithProperties);
	LoadFunction(clSetKernelArgSVMPointer);
	LoadFunction(clSetKernelExecInfo);
	LoadFunction(clEnqueueSVMFree);
	LoadFunction(clEnqueueSVMMemcpy);
	LoadFunction(clEnqueueSVMMemFill);
	LoadFunction(clEnqueueSVMMap);
	LoadFunction(clEnqueueSVMUnmap);
#ifdef CL_USE_DEPRECATED_OPENCL_2_0_APIS
	LoadFunction(clCreateCommandQueue);
	LoadFunction(clCreateSampler);
	LoadFunction(clEnqueueTask);
#endif
#endif

#ifdef CL_VERSION_2_1
	LoadFunction(clSetDefaultDeviceCommandQueue);
	LoadFunction(clGetDeviceAndHostTimer);
	LoadFunction(clGetHostTimer);
	LoadFunction(clCreateProgramWithIL);
	LoadFunction(clCloneKernel);
	LoadFunction(clEnqueueSVMMigrateMem);
	LoadFunction(clGetKernelSubGroupInfo);
#endif

#ifdef CL_VERSION_2_2
	LoadFunction(clSetProgramSpecializationConstant);
#ifdef CL_USE_DEPRECATED_OPENCL_2_2_APIS
	LoadFunction(clSetProgramReleaseCallback);
#endif
#endif

#ifdef CL_VERSION_3_0
	LoadFunction(clSetContextDestructorCallback);
	LoadFunction(clCreateBufferWithProperties);
	LoadFunction(clCreateImageWithProperties);
#endif
}

// Define functions without adresses if no OpenCL support


#ifdef CL_VERSION_1_0

f_clGetPlatformIDs clGetPlatformIDs;
f_clGetPlatformInfo clGetPlatformInfo;
f_clGetDeviceIDs clGetDeviceIDs;
f_clGetDeviceInfo clGetDeviceInfo;
f_clCreateContext clCreateContext;
f_clCreateContextFromType clCreateContextFromType;
f_clRetainContext clRetainContext;
f_clReleaseContext clReleaseContext;
f_clGetContextInfo clGetContextInfo;
f_clRetainCommandQueue clRetainCommandQueue;
f_clReleaseCommandQueue clReleaseCommandQueue;
f_clGetCommandQueueInfo clGetCommandQueueInfo;
f_clCreateBuffer clCreateBuffer;
f_clRetainMemObject clRetainMemObject;
f_clReleaseMemObject clReleaseMemObject;
f_clGetSupportedImageFormats clGetSupportedImageFormats;
f_clGetMemObjectInfo clGetMemObjectInfo;
f_clGetImageInfo clGetImageInfo;
f_clRetainSampler clRetainSampler;
f_clReleaseSampler clReleaseSampler;
f_clGetSamplerInfo clGetSamplerInfo;
f_clCreateProgramWithSource clCreateProgramWithSource;
f_clCreateProgramWithBinary clCreateProgramWithBinary;
f_clRetainProgram clRetainProgram;
f_clReleaseProgram clReleaseProgram;
f_clBuildProgram clBuildProgram;
f_clGetProgramInfo clGetProgramInfo;
f_clGetProgramBuildInfo clGetProgramBuildInfo;
f_clCreateKernel clCreateKernel;
f_clCreateKernelsInProgram clCreateKernelsInProgram;
f_clRetainKernel clRetainKernel;
f_clReleaseKernel clReleaseKernel;
f_clSetKernelArg clSetKernelArg;
f_clGetKernelInfo clGetKernelInfo;
f_clGetKernelWorkGroupInfo clGetKernelWorkGroupInfo;
f_clWaitForEvents clWaitForEvents;
f_clGetEventInfo clGetEventInfo;
f_clRetainEvent clRetainEvent;
f_clReleaseEvent clReleaseEvent;
f_clGetEventProfilingInfo clGetEventProfilingInfo;
f_clFlush clFlush;
f_clFinish clFinish;
f_clEnqueueReadBuffer clEnqueueReadBuffer;
f_clEnqueueWriteBuffer clEnqueueWriteBuffer;
f_clEnqueueCopyBuffer clEnqueueCopyBuffer;
f_clEnqueueReadImage clEnqueueReadImage;
f_clEnqueueWriteImage clEnqueueWriteImage;
f_clEnqueueCopyImage clEnqueueCopyImage;
f_clEnqueueCopyImageToBuffer clEnqueueCopyImageToBuffer;
f_clEnqueueCopyBufferToImage clEnqueueCopyBufferToImage;
f_clEnqueueMapBuffer clEnqueueMapBuffer;
f_clEnqueueMapImage clEnqueueMapImage;
f_clEnqueueUnmapMemObject clEnqueueUnmapMemObject;
f_clEnqueueNDRangeKernel clEnqueueNDRangeKernel;
f_clEnqueueNativeKernel clEnqueueNativeKernel;

#ifdef CL_USE_DEPRECATED_OPENCL_1_0_APIS
/*
 *  WARNING:
 *     This API introduces mutable state into the OpenCL implementation. It has been REMOVED
 *  to better facilitate thread safety.  The 1.0 API is not thread safe. It is not tested by the
 *  OpenCL 1.1 conformance test, and consequently may not work or may not work dependably.
 *  It is likely to be non-performant. Use of this API is not advised. Use at your own risk.
 *
 *  Software developers previously relying on this API are instructed to set the command queue
 *  properties when creating the queue, instead.
 */
f_clSetCommandQueueProperty clSetCommandQueueProperty;

#endif

#endif // 1.0

#ifdef CL_VERSION_1_1

f_clCreateSubBuffer clCreateSubBuffer;
f_clSetMemObjectDestructorCallback clSetMemObjectDestructorCallback;
f_clCreateUserEvent clCreateUserEvent;
f_clSetUserEventStatus clSetUserEventStatus;
f_clSetEventCallback clSetEventCallback;
f_clEnqueueReadBufferRect clEnqueueReadBufferRect;
f_clEnqueueWriteBufferRect clEnqueueWriteBufferRect;
f_clEnqueueCopyBufferRect clEnqueueCopyBufferRect;

/* Deprecated OpenCL 1.1 APIs */

#ifdef CL_USE_DEPRECATED_OPENCL_1_1_APIS

f_clCreateImage2D clCreateImage2D;
f_clCreateImage3D clCreateImage3D;
f_clEnqueueMarker clEnqueueMarker;
f_clEnqueueWaitForEvents clEnqueueWaitForEvents;
f_clEnqueueBarrier clEnqueueBarrier;
f_clUnloadCompiler clUnloadCompiler;
f_clGetExtensionFunctionAddress clGetExtensionFunctionAddress;

#endif

#endif

#ifdef CL_VERSION_1_2

f_clCreateSubDevices clCreateSubDevices;
f_clRetainDevice clRetainDevice;
f_clReleaseDevices clReleaseDevices;
f_clCreateImage clCreateImage;
f_clCreateProgramWithBuiltInKernels clCreateProgramWithBuiltInKernels;
f_clCompileProgram clCompileProgram;
f_clLinkProgram clLinkProgram;
f_clUnloadPlatformCompiler clUnloadPlatformCompiler;
f_clGetKernelArgInfo clGetKernelArgInfo;
f_clEnqueueFillBuffer clEnqueueFillBuffer;
f_clEnqueueFillImage clEnqueueFillImage;
f_clEnqueueMigrateMemObjects clEnqueueMigrateMemObjects;
f_clEnqueueMarkerWithWaitList clEnqueueMarkerWithWaitList;
f_clEnqueueBarrierWithWaitList clEnqueueBarrierWithWaitList;

/* Extension function access
 *
 * Returns the extension function address for the given function name,
 * or NULL if a valid function can not be found.  The client must
 * check to make sure the address is not NULL, before using or
 * calling the returned function address.
 */
f_clGetExtensionFunctionAddressForPlatform clGetExtensionFunctionAddressForPlatform;

#endif

#ifdef CL_VERSION_2_0

f_clCreateCommandQueueWithProperties clCreateCommandQueueWithProperties;
f_clCreatePipe clCreatePipe;
f_clGetPipeInfo clGetPipeInfo;
f_clSVMAlloc clSVMAlloc;
f_clSVMFree clSVMFree;
f_clCreateSamplerWithProperties clCreateSamplerWithProperties;
f_clSetKernelArgSVMPointer clSetKernelArgSVMPointer;
f_clSetKernelExecInfo clSetKernelExecInfo;
f_clEnqueueSVMFree clEnqueueSVMFree;
f_clEnqueueSVMMemcpy clEnqueueSVMMemcpy;
f_clEnqueueSVMMemFill clEnqueueSVMMemFill;
f_clEnqueueSVMMap clEnqueueSVMMap;
f_clEnqueueSVMUnmap clEnqueueSVMUnmap;

#ifdef CL_USE_DEPRECATED_OPENCL_2_0_APIS

/* Deprecated OpenCL 2.0 APIs */

f_clCreateCommandQueue clCreateCommandQueue;
f_clCreateSampler clCreateSampler;
f_clEnqueueTask clEnqueueTask;

#endif

#endif

#ifdef CL_VERSION_2_1

f_clSetDefaultDeviceCommandQueue clSetDefaultDeviceCommandQueue;
f_clGetDeviceAndHostTimer clGetDeviceAndHostTimer;
f_clGetHostTimer clGetHostTimer;
f_clCreateProgramWithIL clCreateProgramWithIL;
f_clCloneKernel clCloneKernel;
f_clEnqueueSVMMigrateMem clEnqueueSVMMigrateMem;
f_clGetKernelSubGroupInfo clGetKernelSubGroupInfo;

#endif

#ifdef CL_VERSION_2_2

f_clSetProgramSpecializationConstant clSetProgramSpecializationConstant;

#ifdef CL_USE_DEPRECATED_OPENCL_2_2_APIS

f_clSetProgramReleaseCallback clSetProgramReleaseCallback;

#endif

#endif

#ifdef CL_VERSION_3_0

f_clSetContextDestructorCallback clSetContextDestructorCallback;
f_clCreateBufferWithProperties clCreateBufferWithProperties;
f_clCreateImageWithProperties clCreateImageWithProperties;

#endif

