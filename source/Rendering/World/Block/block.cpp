#include "rendering/world/block/block.h"
#include "rendering/world/block/blockdatabase.h"

namespace Nocturn
{
	NBlock::NBlock(const uint8 BlockId)
	:
		BlockType(static_cast<EBlockId>(BlockId))
	{}

	NBlock::NBlock(const EBlockId BlockId)
	:
		BlockType(BlockId)
	{}

	void NBlock::operator=(const EBlockId BlockId)
	{
		BlockType = BlockId;
	}

	bool NBlock::operator==(const EBlockId BlockId) const
	{
		return BlockType == BlockId;
	}

	bool NBlock::operator==(const NBlock& Block) const
	{
		return Block == Block.BlockType;
	}

	bool NBlock::operator!=(const NBlock& Block) const
	{
		return Block != Block.BlockType;
	}

	NODISCARD const BlockDataHolder& NBlock::GetData() const
	{
		return BlockDatabase::GetInstance().GetData(static_cast< uint8 >(BlockType));
	}
} // namespace Nocturn