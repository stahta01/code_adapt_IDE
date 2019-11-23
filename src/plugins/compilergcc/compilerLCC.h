#ifndef COMPILER_LCC_H
#define COMPILER_LCC_H

#include <compiler.h>

class CompilerLCC : public Compiler
{
    public:
        CompilerLCC();
        virtual ~CompilerLCC();
#ifdef __WINDOWS__
        virtual bool IsValid();
#endif // __WINDOWS__
        virtual void Reset();
        virtual AutoDetectResult AutoDetectInstallationDir();
    protected:
        virtual Compiler* CreateCopy();
    private:
        bool m_RegistryUpdated;
};

#endif // COMPILER_LCC_H
