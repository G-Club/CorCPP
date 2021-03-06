#include "stringtools.h"
#include "../common.h"


static const unsigned char aucCRCHi[] = {
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x00, 0xC1, 0x81, 0x40,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40, 0x01, 0xC0, 0x80, 0x41, 0x01, 0xC0, 0x80, 0x41,
    0x00, 0xC1, 0x81, 0x40
};

static const unsigned char aucCRCLo[] = {
    0x00, 0xC0, 0xC1, 0x01, 0xC3, 0x03, 0x02, 0xC2, 0xC6, 0x06, 0x07, 0xC7,
    0x05, 0xC5, 0xC4, 0x04, 0xCC, 0x0C, 0x0D, 0xCD, 0x0F, 0xCF, 0xCE, 0x0E,
    0x0A, 0xCA, 0xCB, 0x0B, 0xC9, 0x09, 0x08, 0xC8, 0xD8, 0x18, 0x19, 0xD9,
    0x1B, 0xDB, 0xDA, 0x1A, 0x1E, 0xDE, 0xDF, 0x1F, 0xDD, 0x1D, 0x1C, 0xDC,
    0x14, 0xD4, 0xD5, 0x15, 0xD7, 0x17, 0x16, 0xD6, 0xD2, 0x12, 0x13, 0xD3,
    0x11, 0xD1, 0xD0, 0x10, 0xF0, 0x30, 0x31, 0xF1, 0x33, 0xF3, 0xF2, 0x32,
    0x36, 0xF6, 0xF7, 0x37, 0xF5, 0x35, 0x34, 0xF4, 0x3C, 0xFC, 0xFD, 0x3D,
    0xFF, 0x3F, 0x3E, 0xFE, 0xFA, 0x3A, 0x3B, 0xFB, 0x39, 0xF9, 0xF8, 0x38,
    0x28, 0xE8, 0xE9, 0x29, 0xEB, 0x2B, 0x2A, 0xEA, 0xEE, 0x2E, 0x2F, 0xEF,
    0x2D, 0xED, 0xEC, 0x2C, 0xE4, 0x24, 0x25, 0xE5, 0x27, 0xE7, 0xE6, 0x26,
    0x22, 0xE2, 0xE3, 0x23, 0xE1, 0x21, 0x20, 0xE0, 0xA0, 0x60, 0x61, 0xA1,
    0x63, 0xA3, 0xA2, 0x62, 0x66, 0xA6, 0xA7, 0x67, 0xA5, 0x65, 0x64, 0xA4,
    0x6C, 0xAC, 0xAD, 0x6D, 0xAF, 0x6F, 0x6E, 0xAE, 0xAA, 0x6A, 0x6B, 0xAB,
    0x69, 0xA9, 0xA8, 0x68, 0x78, 0xB8, 0xB9, 0x79, 0xBB, 0x7B, 0x7A, 0xBA,
    0xBE, 0x7E, 0x7F, 0xBF, 0x7D, 0xBD, 0xBC, 0x7C, 0xB4, 0x74, 0x75, 0xB5,
    0x77, 0xB7, 0xB6, 0x76, 0x72, 0xB2, 0xB3, 0x73, 0xB1, 0x71, 0x70, 0xB0,
    0x50, 0x90, 0x91, 0x51, 0x93, 0x53, 0x52, 0x92, 0x96, 0x56, 0x57, 0x97,
    0x55, 0x95, 0x94, 0x54, 0x9C, 0x5C, 0x5D, 0x9D, 0x5F, 0x9F, 0x9E, 0x5E,
    0x5A, 0x9A, 0x9B, 0x5B, 0x99, 0x59, 0x58, 0x98, 0x88, 0x48, 0x49, 0x89,
    0x4B, 0x8B, 0x8A, 0x4A, 0x4E, 0x8E, 0x8F, 0x4F, 0x8D, 0x4D, 0x4C, 0x8C,
    0x44, 0x84, 0x85, 0x45, 0x87, 0x47, 0x46, 0x86, 0x82, 0x42, 0x43, 0x83,
    0x41, 0x81, 0x80, 0x40
};

unsigned short StringTools::calc_crc16(unsigned char *pucFrame, unsigned int usLen)
{
    unsigned char ucCRCHi = 0xFF;
    unsigned char ucCRCLo = 0xFF;
    int iIndex;
    while (usLen--)
    {
        iIndex = ucCRCLo ^ *(pucFrame++);

        ucCRCLo = (unsigned char)(ucCRCHi ^ aucCRCHi[iIndex]);

        ucCRCHi = aucCRCLo[iIndex];
    }

    return (unsigned short)(ucCRCHi << 8 | ucCRCLo);
}

StringTools::StringTools()
{

}

void StringTools::StringSplit(std::string str, std::string &split, std::vector<std::string> *result)
{
    if (result == NULL)
    {
        return;
    }
    std::string::size_type pos = str.find(split);
    while (pos != std::string::npos)
    {
        std::string sub = str.substr(0, pos);
        if (sub.length() > 0)
        {
            result->push_back(sub);
        }
        str = str.substr(sub.length() + 1);
        pos = str.find(split);
    }

    if (str.length() > 0)
    {
        result->push_back(str);
    }

}


void StringTools::StringSplit(std::string str, const char *split, std::vector<std::string> *result)
{
    if (result == NULL)
    {
        return;
    }
    std::string sp(split);
    StringSplit(str,sp,result);
}

std::string StringTools::StringTrim(std::string &pstr)
{
    if (pstr.length() < 1)
    {
        return "";
    }
    std::string::iterator it = pstr.begin();

    while (it != pstr.end())
    {
        if (*it != ' ')
        {
            break;
        }
        it = pstr.erase(it);
    }

    std::string::reverse_iterator rit = pstr.rbegin();
    while (rit != pstr.rend())
    {
        if (*rit != ' ')
        {
            break;
        }
        rit = std::string::reverse_iterator(pstr.erase((++rit).base()));
    }

    return pstr;
}

bool StringTools::DomainValid(const string &domain)//域名验证
{
    int isok= IsGsmrDomain(domain);
    if(isok==DnsDomainType::DNS_GSMR_NOT)
    {
        return false;
    }
    return true;

    std::regex domainPattern("([0-9A-Za-z\\-_\\.]+)\\.([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
    try
    {
        return regex_match(domain,domainPattern);
    }catch(std::exception &ex)
    {
        WLOG_ERROR(LOG_ERR_MODEL,"GSMRDNS##%s:%d->domain regex valid error:%s",__FILE__,__LINE__,ex.what());

        return false;
    }
}

bool StringTools::DomainValid(const char *domain)//域名验证
{
    std::string s=domain;
    return DomainValid(s);
}

bool StringTools::IpAddressValid(const std::string &address)//IP验证
{
    std::regex ipPattern("((25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])\\.){3}(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9][0-9]|[0-9])");
    try
    {
        return  regex_match(address,ipPattern);
    }
    catch(std::exception &ex)
    {
        WLOG_ERROR(LOG_ERR_MODEL,"GSMRDNS##%s:%d->IpAddress regex valid error:%s",__FILE__,__LINE__,ex.what());
        return false;
    }
}

bool StringTools::IpAddressValid(const char *address)//IP验证
{
    std::string addr=address;
    return IpAddressValid(addr);
}

bool StringTools::DotIpToCharArray(string domain,char *result=NULL)
{
    if(result==NULL)
    {
        return false;
    }
    std::vector<std::string> vec;
    StringSplit(domain,".",&vec);
    if(vec.size() !=4)
    {
        return false;
    }
    for(int i=0;i<vec.size();++i)
    {
        int sint=std::stoi(vec[i]);
        result[i]=sint;
    }
    return true;
}

//点分十进制变成char的数组形式  dns响应会用
bool StringTools::DotIpToCharArray(const char *address,char *result)//IP验证
{
    std::string addr=address;
    return DotIpToCharArray(addr,result);
}

int  StringTools::IsGsmrDomain(const std::string &domain)
{
    return IsGsmrDomain(domain.c_str(),domain.length());
}

int StringTools::IsGsmrDomain(const char* pName, unsigned int uLen)
{
    int ii=0, jj=0;
    char szBuff[2048] = {0};
    const char* pIdx = pName;

    //下面的整个循环是把域名 gsmr.b.prac.cn 这个格式以.分割成了不同的字符串 分别以100间隔 存在了szBuff这个大buffer里了  ii记录的是这个大buffer里面的个数
    //ii<20 是因为buffer有2048大 100×20<2048
    for( ii = 0, jj = 0; *pIdx && ii < 20; ++pIdx )
    {
        if( *pIdx == '.' )
        {
            if( (jj > 98) || !szBuff[100*ii])
            {
                return DnsDomainType::DNS_GSMR_NOT;
            }

            ++ii; jj = 0;
            continue;
        }

        szBuff[100 * ii + jj] = *pIdx;

        ++jj;
    }
    //这里要不是0 就意味着超出了20个
    if( !*pIdx )
    {
        ++ii;
    }
    // return strcmp("daisy.ubuntu.com", pName);
    //小于2压根就不是域名的格式
    if( ii < 2 )
    {
        return DnsDomainType::DNS_GSMR_NOT;
    }
    //最后一个不能是gprs结尾
    if( strcasecmp("gprs", szBuff + ((ii-1)*100)) )
    {
        return DnsDomainType::DNS_GSMR_NOT;
    }
    // if( 4 == ii && !strcmp("ms", szBuff + 200) && !strcmp("cir", szBuff))
    //在有4个的情况下  abc.bc.ms.com 第三个要为ms
    if( 4 == ii && !strcasecmp("ms", szBuff + 200) )
    {
        return DnsDomainType::DNS_GSMR_TRAIN;
    }

    if( 5 == ii && !strcasecmp("mcc460", szBuff + 300) && !strcasecmp("mnc020", szBuff + 200)
            && !strncasecmp("lac", szBuff + 100, 3) && !strncasecmp("rac", szBuff, 3) )
    {
        return DnsDomainType::DNS_GSMR_RAI;
    }

    if( 3 < ii && !strcasecmp("mcc460", szBuff + ((ii-2)*100)) && !strcasecmp("mnc020", szBuff + ((ii-3)*100)))
    {
        return DnsDomainType::DNS_GSMR_APN;	// or DNS_GSMR_OTH
    }

    if( 2 < ii && !strcasecmp("ne", szBuff + ((ii-2)*100)) )
    {
        return DnsDomainType::DNS_GSMR_NE;
    }

    return DnsDomainType::DNS_GSMR_NOT;
}

char*  StringTools::strnstr(const char *s, const char *find, size_t slen)
{
    char c, sc;
    size_t len;

    if ((c = *find++) != '\0') {
        len = strlen(find);
        do {
            do {
                if (slen-- < 1 || (sc = *s++) == '\0')
                    return (NULL);
            } while (sc != c);
            if (len > slen)
                return (NULL);
        } while (strncmp(s, find, len) != 0);
        s--;
    }
    return ((char *)s);
}


unsigned char*  StringTools::ustrnstr(unsigned char* s,unsigned char* find, size_t slen)
{
    unsigned  char c, sc;
    size_t len;

    if ((c = *find++) != '\0')
    {
        len = strlen((char*)find);
        do
        {
            do
            {
                if (slen-- < 1 || (sc = *s++) == '\0')
                {
                    return (NULL);
                }
            } while (sc != c);
            if (len > slen)
            {
                return (NULL);
            }
        } while (strncmp((char*)s, (char*)find, len) != 0);
        s--;
    }
    return (s);
}


StringTools::~StringTools()
{

}
