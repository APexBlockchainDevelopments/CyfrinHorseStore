# Aderyn Analysis Report

This report was generated by [Aderyn](https://github.com/Cyfrin/aderyn), a static analysis tool built by [Cyfrin](https://cyfrin.io), a blockchain security company. This report is not a substitute for manual audit or security review. It should not be relied upon for any purpose other than to assist in the identification of potential security vulnerabilities.
# Table of Contents

- [Summary](#summary)
  - [Files Summary](#files-summary)
  - [Files Details](#files-details)
  - [Issue Summary](#issue-summary)
- [Low Issues](#low-issues)
  - [L-1: PUSH0 is not supported by all chains](#l-1-push0-is-not-supported-by-all-chains)


# Summary

## Files Summary

| Key | Value |
| --- | --- |
| .sol Files | 3 |
| Total nSLOC | 28 |


## Files Details

| Filepath | nSLOC |
| --- | --- |
| src/horseStoreV1/HorseStoreYul.sol | 16 |
| src/horseStoreV1/interfaces/ISimpleStorage.sol | 5 |
| src/horseStoreV2/IHorseStore.sol | 7 |
| **Total** | **28** |


## Issue Summary

| Category | No. of Issues |
| --- | --- |
| Critical | 0 |
| High | 0 |
| Medium | 0 |
| Low | 1 |
| NC | 0 |


# Low Issues

## L-1: PUSH0 is not supported by all chains

Solc compiler version 0.8.20 switches the default target EVM version to Shanghai, which means that the generated bytecode will include PUSH0 opcodes. Be sure to select the appropriate EVM version in case you intend to deploy on a chain other than mainnet like L2 chains that may not support PUSH0, otherwise deployment of your contracts will fail.

- Found in src/horseStoreV1/HorseStoreYul.sol [Line: 2](src/horseStoreV1/HorseStoreYul.sol#L2)

	```solidity
	pragma solidity 0.8.20;
	```

- Found in src/horseStoreV1/interfaces/ISimpleStorage.sol [Line: 2](src/horseStoreV1/interfaces/ISimpleStorage.sol#L2)

	```solidity
	pragma solidity 0.8.20;
	```

- Found in src/horseStoreV2/IHorseStore.sol [Line: 2](src/horseStoreV2/IHorseStore.sol#L2)

	```solidity
	pragma solidity 0.8.20;
	```



