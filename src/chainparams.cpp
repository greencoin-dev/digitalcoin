// Copyright (c) 2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include "chainparams.h"

#include "assert.h"
#include "core.h"
#include "protocol.h"
#include "util.h"

#include <boost/assign/list_of.hpp>

using namespace boost::assign;

//
// Main network
//

unsigned int pnSeed[] =
{
    0xE195C721, 0x31D3A142, 0x92B9B572, 0xA2F3716E, 0x5F551D90
};

class CMainParams : public CChainParams {
public:
    CMainParams() {
	// The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        pchMessageStart[0] = 0xfb;
        pchMessageStart[1] = 0xc0;
        pchMessageStart[2] = 0xb6;
        pchMessageStart[3] = 0xdb;
	// UPDATE THIS
        vAlertPubKey = ParseHex("04016c44069c3152982413d3ba3bf262a3a4d3ddad859ba78e0d744f5c67c2205d2aa2122e6c62b6310dad2d1e2f7e39028455ff1dbb26511c60fc96c8b4560c43");
        nDefaultPort = 11036;
        nRPCPort = 21036;
        bnProofOfWorkLimit[ALGO_SHA256D] = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_SCRYPT]  = CBigNum(~uint256(0) >> 20);
        bnProofOfWorkLimit[ALGO_X11] = CBigNum(~uint256(0) >> 20);

	// Build the genesis block. Note that the output of the genesis coinbase cannot
        // be spent as it did not originally exist in the database.
        const char* pszTimestamp = "GreenCoin - 6/7/2014 Saturday, 1402160424";
        CTransaction txNew;
        txNew.vin.resize(1);
        txNew.vout.resize(1);
        txNew.vin[0].scriptSig = CScript() << 486604799 << CScriptNum(4) << vector<unsigned char>((const unsigned char*)pszTimestamp, (const unsigned char*)pszTimestamp + strlen(pszTimestamp));
        txNew.vout[0].nValue = 25 * COIN;
	txNew.vout[0].scriptPubKey = GetFoundationScript();
        genesis.vtx.push_back(txNew);
        genesis.hashPrevBlock = 0;
        genesis.hashMerkleRoot = genesis.BuildMerkleTree();
        genesis.nVersion = 1;
        genesis.nTime    = 1402160424;
        genesis.nBits    = 0x1e0ffff0;
        genesis.nNonce   = 2046606399;

        hashGenesisBlock = genesis.GetHash();
        assert(hashGenesisBlock == uint256("0x63a432df624fb9761b4436a81a74bdbbb6b7aead9c1b4cb9c0fdcbfe3b9c00c7"));
        assert(genesis.hashMerkleRoot == uint256("0x135aab1273776b7fd6a69c9e118c47aef52c1ab131c14f6a7a86b4cb40cd0ae2"));

        vSeeds.push_back(CDNSSeedData("digitalcoin.co seed #1", "digitalcoin.co"));        
		vSeeds.push_back(CDNSSeedData("digitalcoin.co seed #2", "game.digitalcoin.co"));
		vSeeds.push_back(CDNSSeedData("digitalcoin.co seed #3", "dev.digitalcoin.co"));
		vSeeds.push_back(CDNSSeedData("ahmed seed #1", "178.62.28.81"));
        //vSeeds.push_back(CDNSSeedData("digihash.co seed #3", "seed3.digihash.co"));
        //vSeeds.push_back(CDNSSeedData("love2hash.com seed #4", "seed4.love2hash.com"));
        //vSeeds.push_back(CDNSSeedData("digiexplorer.info seed #5", "seed5.digiexplorer.info"));

        base58Prefixes[PUBKEY_ADDRESS] = list_of(20);
        base58Prefixes[SCRIPT_ADDRESS] = list_of(20);
        base58Prefixes[SECRET_KEY] =     list_of(20);
        base58Prefixes[EXT_PUBLIC_KEY] = list_of(0x04)(0x88)(0xB2)(0x1E);
        base58Prefixes[EXT_SECRET_KEY] = list_of(0x04)(0x88)(0xAD)(0xE4);

        // Convert the pnSeeds array into usable address objects.
        for (unsigned int i = 0; i < ARRAYLEN(pnSeed); i++)
        {
            // It'll only connect to one or two seed nodes because once it connects,
            // it'll get a pile of addresses with newer timestamps.
            // Seed nodes are given a random 'last seen time' of between one and two
            // weeks ago.
            const int64_t nOneWeek = 7*24*60*60;
            struct in_addr ip;
            memcpy(&ip, &pnSeed[i], sizeof(ip));
            CAddress addr(CService(ip, GetDefaultPort()));
            addr.nTime = GetTime() - GetRand(nOneWeek) - nOneWeek;
            vFixedSeeds.push_back(addr);
        }
    }

    virtual const CBlock& GenesisBlock() const { return genesis; }
    virtual Network NetworkID() const { return CChainParams::MAIN; }

    virtual const vector<CAddress>& FixedSeeds() const {
        return vFixedSeeds;
    }
protected:
    CBlock genesis;
    vector<CAddress> vFixedSeeds;
};
static CMainParams mainParams;


//
// Testnet (v3)
//
class CTestNetParams : public CMainParams {
public:
    CTestNetParams() {
        // The message start string is designed to be unlikely to occur in normal data.
        // The characters are rarely used upper ASCII, not valid as UTF-8, and produce
        // a large 4-byte int at any alignment.
        nDefaultPort = 12025;
        nRPCPort = 14023;
        strDataDir = "testnet3";

	vFixedSeeds.clear();
        vSeeds.clear();

    }
    virtual Network NetworkID() const { return CChainParams::TESTNET; }
};
static CTestNetParams testNetParams;


//
// Regression test
//
class CRegTestParams : public CTestNetParams {
public:
    CRegTestParams() {
        pchMessageStart[0] = 0xfa;
        pchMessageStart[1] = 0xb3;
        pchMessageStart[2] = 0xb2;
        pchMessageStart[3] = 0xdb;
        //nSubsidyHalvingInterval = 150;
       // bnProofOfWorkLimit = CBigNum();
        genesis.nTime = 1392796564;
        genesis.nBits = 0x207fffff;
        genesis.nNonce = 961533;
        hashGenesisBlock = genesis.GetHash();
        nDefaultPort = 18444;
        strDataDir = "regtest";
        //assert(hashGenesisBlock == uint256("0x0f9188f13cb7b2c71f2a335e3a4fc328bf5beb436012afca590b1a11466e2206"));

        vSeeds.clear();  // Regtest mode doesn't have any DNS seeds.
    }

    virtual bool RequireRPCPassword() const { return false; }
    virtual Network NetworkID() const { return CChainParams::REGTEST; }
};
static CRegTestParams regTestParams;

static CChainParams *pCurrentParams = &mainParams;

const CChainParams &Params() {
    return *pCurrentParams;
}

void SelectParams(CChainParams::Network network) {
    switch (network) {
        case CChainParams::MAIN:
            pCurrentParams = &mainParams;
            break;
        case CChainParams::TESTNET:
            pCurrentParams = &testNetParams;
            break;
        case CChainParams::REGTEST:
            pCurrentParams = &regTestParams;
            break;
        default:
            assert(false && "Unimplemented network");
            return;
    }
}

bool SelectParamsFromCommandLine() {
    bool fRegTest = GetBoolArg("-regtest", false);
    bool fTestNet = GetBoolArg("-testnet", false);

    if (fTestNet && fRegTest) {
        return false;
    }

    if (fRegTest) {
        SelectParams(CChainParams::REGTEST);
    } else if (fTestNet) {
        SelectParams(CChainParams::TESTNET);
    } else {
        SelectParams(CChainParams::MAIN);
    }
    return true;
}
