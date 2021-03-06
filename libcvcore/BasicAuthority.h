
#pragma once

#include "SealEngine.h"

namespace dev
{
namespace eth
{

class BasicAuthority: public SealEngineBase
{
public:
	std::string name() const override { return "BasicAuthority"; }
	unsigned revision() const override { return 0; }
	unsigned sealFields() const override { return 1; }
	bytes sealRLP() const override { return rlp(Signature()); }

	void populateFromParent(BlockHeader&, BlockHeader const&) const override;
	StringHashMap jsInfo(BlockHeader const& _bi) const override;
	void verify(Strictness _s, BlockHeader const& _bi, BlockHeader const& _parent, bytesConstRef _block) const override;
	bool shouldSeal(Interface*) override;
	void generateSeal(BlockHeader const& _bi, bytes const& _block_data = bytes()) override;

	static Signature sig(BlockHeader const& _bi) { return _bi.seal<Signature>(); }
	static BlockHeader& setSig(BlockHeader& _bi, Signature const& _sig) { _bi.setSeal(_sig); return _bi; }
	void setSecret(Secret const& _s) { m_secret = _s; }
	static void init();

private:
	bool onOptionChanging(std::string const& _name, bytes const& _value) override;

	Secret m_secret;
	AddressHash m_authorities;
};

}
}
