object "HorseStoreYul" {
    code {
        //Contract Deployment
        datacopy(0, dataoffset("runtime"), datasize("runtime"))
        return(0, datasize("runtime"))
    }
    object "runtime" {
        code {
            //function dispatcher
            switch selector()
            //updateHourseNubmer (uint256)
            case 0xcdfead2e {
                storeNumber(decodeAsUint(0))
            }
            //read number of Horses
            case 0xe026c017{
                returnUint(readNumber())
            }
            default{
                revert(0,0)
            }

            function storeNumber(newNumber) {
                sstore(0, newNumber)
            }

            function readNumber() -> storedNumber{
                storedNumber := sload(0)
            }

            /* ---------- calldata decoding functions ----------- */
            function selector() -> s {
                s := div(calldataload(0), 0x100000000000000000000000000000000000000000000000000000000)
            }

            function decodeAsUint(offset) -> v {
                 let pos := add(4, mul(offset, 0x20))
                if lt(calldatasize(), add(pos, 0x20)){
                    revert (0,0)
                }
                v := calldataload(pos)
            }

            function returnUint(v) {
                mstore(0, v)
                return(0, 0x20)
            }
        }
    }
}