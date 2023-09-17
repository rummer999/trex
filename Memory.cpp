#pragma once
#include <iostream>
#include <sstream>
#include <sys/uio.h>
#include <stdexcept>

namespace mem
{
    pid_t m_pid = 0;

    pid_t GetPID()
    {
        if (m_pid > 0)
            return m_pid;
        char buf[512];
        FILE *cmd_pipe = popen("pidof -s r5apex.exe", "r");
        fgets(buf, 512, cmd_pipe);
        pid_t pid = strtoul(buf, NULL, 10);
        pclose(cmd_pipe);
        m_pid = pid;
        return pid;
    }

    bool Read(long address, void *pBuff, size_t size)
    {
        if (size == 0)
            return false;
        void *pAddress = (void *)address;
        pid_t pid = GetPID();
        struct iovec iovLocalAddressSpace[1]{0};
        struct iovec iovRemoteAddressSpace[1]{0};
        iovLocalAddressSpace[0].iov_base = pBuff;
        iovLocalAddressSpace[0].iov_len = size;
        iovRemoteAddressSpace[0].iov_base = pAddress;
        iovRemoteAddressSpace[0].iov_len = size;
        ssize_t sSize = process_vm_readv(
            pid,
            iovLocalAddressSpace,
            1,
            iovRemoteAddressSpace,
            1,
            0);
        if (sSize == (ssize_t)size)
            return true;
        else if (sSize == 0)
            return false;
        return false;
    }

    bool Write(long address, void *pBuff, size_t size)
    {
        if (size == 0)
            return false;
        void *pAddress = (void *)address;
        pid_t pid = GetPID();
        struct iovec iovLocalAddressSpace[1]{0};
        struct iovec iovRemoteAddressSpace[1]{0};
        iovLocalAddressSpace[0].iov_base = pBuff;
        iovLocalAddressSpace[0].iov_len = size;
        iovRemoteAddressSpace[0].iov_base = pAddress;
        iovRemoteAddressSpace[0].iov_len = size;
        ssize_t sSize = process_vm_writev(
            pid,
            iovLocalAddressSpace,
            1,
            iovRemoteAddressSpace,
            1,
            0);
        if (sSize == (ssize_t)size)
            return true;
        else if (sSize == 0)
            return false;
        return false;
    }

    std::string ReadString(long address)
    {
        int size = sizeof(std::string);
        char buffer[size] = {0};
        bool success = Read(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to read String at address: " + std::to_string(address));
        return std::string(buffer);
    }

    short ReadShort(long address)
    {
        int size = sizeof(short);
        short buffer;
        bool success = Read(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to read short at address: " + std::to_string(address));
        return buffer;
    }

    void WriteShort(long address, short num)
    {
        int size = sizeof(short);
        short buffer = num;
        bool success = Write(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to write short at address: " + std::to_string(address));
    }

    int ReadInt(long address)
    {
        int size = sizeof(int);
        int buffer;
        bool success = Read(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to read int at address: " + std::to_string(address));
        return buffer;
    }

    void WriteInt(long address, int num)
    {
        int size = sizeof(int);
        int buffer = num;
        bool success = Write(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to write int at address: " + std::to_string(address));
    }

    float ReadFloat(long address)
    {
        int size = sizeof(float);
        float buffer;
        bool success = Read(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to read float at address: " + std::to_string(address));
        return buffer;
    }

    void WriteFloat(long address, float num)
    {
        int size = sizeof(float);
        float buffer = num;
        bool success = Write(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to write float at address: " + std::to_string(address));
    }

    long ReadLong(long address)
    {
        int size = sizeof(long);
        long buffer;
        bool success = Read(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to read long at address: " + std::to_string(address));
        return buffer;
    }

    void WriteLong(long address, long num)
    {
        int size = sizeof(long);
        long buffer = num;
        bool success = Write(address, &buffer, size);
        if (!success)
            throw std::runtime_error("Failed to write long at address: " + std::to_string(address));
    }

    std::string convertPointerToHexString(long pointer)
    {
        std::stringstream stream;
        stream << "0x" << std::hex << pointer;
        std::string result(stream.str());
        return result;
    }

    std::string get_client_class_name(long entity_ptr)
    {
        long client_networkable_vtable;
        long get_client_entity;
        int offset;
        long network_name_ptr;
        char buffer[32];
        // Read the ClientClass's network name for to given entity
        client_networkable_vtable = ReadLong(entity_ptr + 3 * 8);
        get_client_entity = ReadLong(client_networkable_vtable + 3 * 8);
        offset = ReadInt(get_client_entity + 3);
        network_name_ptr = ReadLong(get_client_entity + offset + 7 + 16);
        Read(network_name_ptr, buffer, 32);
        std::string result;
        // Return up to 32 chars from the network name
        size_t len;
        for (len = 0; len < 32; ++len)
            if (buffer[len] == '\0')
                break;
        result.assign(buffer, len);
        return result;
    }
}

