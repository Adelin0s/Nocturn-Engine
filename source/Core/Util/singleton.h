/****************************************************************************************
 * @ Author: Cucorianu Eusebiu Adelin                                                   *
 * @ Create Time: 30-07-2021 18:59:35                                                   *
 * @ Modified by: Cucorianu Eusebiu Adelin                                              *
 * @ Modified time: 28-10-2021 17:14:07                                                 *
 * @ Description:                                                                       *
 ****************************************************************************************/

#ifndef SINGLETON_H
#define SINGLETON_H

namespace Nocturn::core
{
    class Singleton
    {
    public:
        Singleton(const Singleton &) = delete;
        Singleton(const Singleton &&) = delete;

        Singleton &operator=(const Singleton &) = delete;
        Singleton &operator=(Singleton &&) = delete;

    private:
    };
}
#endif