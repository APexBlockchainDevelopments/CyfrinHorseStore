// SPDX-License-Identifier: GPL-3.0-only
pragma solidity 0.8.20;

import {ERC721Enumerable, ERC721} from "@openzeppelin/contracts/token/ERC721/extensions/ERC721Enumerable.sol";
import {IHorseStore} from "./IHorseStore.sol";


contract HorseStore is IHorseStore, ERC721Enumerable {
    string constant NFT_NAME = "HorseStore";
    string constant NFT_SYMBOL = "HS";
    uint256 public constant HORSE_HAPPY_IF_FED_WITHIN = 1 days;

    mapping(uint256 id => uint256 lastFedTimeStamp) public horseIdToFedTimeStamp;

    constructor () ERC721(NFT_NAME, NFT_SYMBOL) {}

    function mintHorse() external {
        _safeMint(msg.sender, totalSupply());
    }

    function feedHorse(uint256 horseId) external {
        horseIdToFedTimeStamp[horseId] = block.timestamp;
    }

    function isHappyHorse(uint256 horseId) external view returns(bool){
        if (horseIdToFedTimeStamp[horseId] <= block.timestamp - HORSE_HAPPY_IF_FED_WITHIN) {
            return false;
        }
        return true;
    }
}

