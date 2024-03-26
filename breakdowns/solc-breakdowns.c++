// 0x6080604052348015600e575f80fd5b5060a58061001b5f395ff3fe6080604052348015600e575f80fd5b50600436106030575f3560e01c8063cdfead2e146034578063e026c017146045575b5f80fd5b6043603f3660046059565b5f55565b005b5f5460405190815260200160405180910390f35b5f602082840312156068575f80fd5b503591905056fea26469706673582212200c25d27aff771cf69e86dc40e75701cba871cab8581706c8956ba62666eeb72c64736f6c63430008140033

//1 Contract creation code
// Free memory pointer
PUSH1 0x80  //[0x80]
PUSH1 0x40  //[0x40, 0x80]
MSTORE      //Loads a free member pointer. "Hey where can se stick something in memory?"

//if there is value vert!, other wise jump to continue execution
CALLVALUE //[msg.value] 
DUP1    //[msg.value, msg.value]
ISZERO  //[msg.vaue == 0, msg.value]
PUSH1 0x0e  // [0x0e, msg.vaue == 0, msg.value]
JUMPI   // [0x0e, msg.vaue == 0, msg.value] //jump if msg.value is iszero
PUSH0   // [0x00, msg.value] 
DUP1    // [0x00, 0x00, msg.value]
REVERT  // [msg.value]


//Sticks runtiem code on chain
JUMPDEST //jump dest if msg.value == 0
POP     // []
PUSH1 0xa5 //[0xa5]
DUP1    //[0xa5, 0xa5]
PUSH2 0x001b //[0x001b, 0xa5, 0xa5]
PUSH0   //[0x00, 0x001b, 0xa5, 0xa5]
CODECOPY //[destOffset, offset (begginning of code), size to copy] [0xa5]  Memory [runtomeCode]
PUSH0 //[0x00, 0xa5]
RETURN //[0x00, 0xa5] []
INVALID //[]

//2 Runtime code
//Entry point of all calls
//Free memory pointer
PUSH1 0x80
PUSH1 0x40
MSTORE

//Solidity checking function to see if it's payable
CALLVALUE  //[msg.value]
DUP1     //[msg.vaue, msg.value]
ISZERO //[msg.value == 0, msg.value]
PUSH1 0x0e
JUMPI    // [0x0e, msg.vaue == 0, msg.value] //jump if msg.value is is not zero
PUSH0   // [0x00, msg.value] 
DUP1    // [0x00, 0x00, msg.value]
REVERT  // [msg.value]
 
// If msg.value == 0 start here
//checking to see if there is enough call data for a function selector
JUMPDEST //[msg.value]
POP //[]
PUSH1 0x04 //[0x04]
CALLDATASIZE //[calldat_size, 0x04]
LT              //a < b is calldata size 0x04
PUSH1 0x30      //[0x30, calldatasize < 0x04]
JUMPI       //if call data is too small jump to 0x30


//function dispatcher system
PUSH0  //[0]
CALLDATALOAD //[calldata, 0x0]
PUSH1 0xe0 //[0ex8, calldata, 0x0]
SHR     //shr -> get first 4 bytes of call data [func_sel, 0x0]
DUP1    //[func, func, 0x0]
PUSH4 0xcdfead2e    //[0xcdfead2e, func, 0x0]
EQ  //are they equal? [0xcdfead2e == func, 0x0]
PUSH1 0x34  //[0x34, 0xcdfead2e == func, 0x0]
JUMPI //jump to 0x34 if the func selector matches 0xcdfead2e  -> set number of horses
DUP1  //[func, func]
PUSH4 0xe026c017 //[0xe026c017, func, func]
EQ  //[func_selector == 0e026c017, func_sec]
PUSH1 0x45 //[0x45, func_selector == 0e026c017, func_sec]
JUMPI  //0x45 jump to 0x34 if the func selector matches 0xcdfead2e

//calldata_jump
JUMPDEST //[]
PUSH0   //[0]
DUP1        //[0,0]
REVERT //[revert]


//update horseNumber jump dest 1
JUMPDEST  //[func, ]
PUSH1 0x43  //[0x43, func, ]
PUSH1 0x3f  //[0x43, 0x3f, func, ]
CALLDATASIZE    //[calldatasize, 0x43, 0x3f, func ]
PUSH1 0x04  //[0x04, calldatasize, 0x43, 0x3f, func ] 
PUSH1 0x59   //[0x59, 0x04, calldatasize, 0x43, 0x3f, func ]
JUMP    //jumps to pc most recently on stack    [0x59, 0x04, calldatasize, 0x43, 0x3f, func ]

// updateHorseNumber jump dest 4
// We can FINALLY run sstore to save our value to storage. Only NOW that we have:
// 1. Done the function dispatch
// 2. Checked for any msg.value
// 3. Checked to see if the calldata is big enough to add a uint256
// 4. Removed the function selector from the calldata 
JUMPDEST        // [calldata (without function selector), 43, function_selector]
PUSH0            // [0, calldata, 43, function_selector]
SSTORE           // [43, function_selector]
JUMP              // [function_selector]

// updateHorseNumber jump dest 5
// And we are done!!
JUMPDEST       // [function_selector]     
STOP              // [function_selector]

//get horseNumber dest 1
JUMPDEST   //[func_sel]
PUSH0    //[0x0, func_sel] //0x0 is like a place holder for sload
SLOAD    //[value at storeage slot 00, func_sel]
PUSH1 0x40  //[0x40, value at storeage slot 00, func_sel]
MLOAD    //[memoryavlue at 0x40(free memory pointer, value at storeage slot 0, func_sel]
SWAP1    //[storage value at slot 0, free memory pointer, function_selector]
DUP2       // [free memory pointer, storage value at slot 0, free memory pointer, function_selector]  
// The MSTORE function will put our `storage value at slot 0` into memory where our free memory pointer says free memory starts (0x40)
MSTORE       // [free memory pointer, function_selector]
PUSH1 0x20   // [0x20, free memory pointer, function_selector]
ADD          // [20 + free memory pointer, function_selector]
PUSH1 0x40   // [0x40, 20 + free memory pointer, function_selector]
MLOAD       // [memory at 0x40 (free memory pointer!), 20 + free memory pointer, function_selector]
DUP1        // [free memory pointer, free memory pointer, 20 + free memory pointer, function_selector]
SWAP2       // [20 + free memory pointer, free memory pointer, free memory pointer, function_selector]
SUB              // [(20 + free memory pointer) - (free memory pointer) aka 20, free memory pointer, function_selector]
SWAP1         // [free memory pointer, 20, function_selector]
// To return our value, we need to point to storage. Since we placed our SLOADed value into the free memory pointer location, we can just return that!
// The 20 stands for how big it should be. 0x20 == 32 bytes, a uint256 is 32 bytes.
RETURN

//update horseNumber jupm dest 2
JUMPDEST    //  [0x04, calldatasize, 0x43, 0x3f, func ]
PUSH0   //  [0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
PUSH1 0x20  ////  [0x20, 0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
DUP3    //  [0x04, 0x20, 0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
DUP5    //  [calldatasize, 0x04, 0x20, 0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
SUB     //  [calldatasize - 0x04, 0x20, 0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
// is there more call data than just the functino selector?
//function selector (4) + bytes32 then this would equate to false
SLT     //  [calldatasize - 0x04 < 0x20, 0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
ISZERO   //  [more call data than selector, 0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
PUSH1 0x68   //  [0x68, more call data than selector, 0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
JUMPI   //  [0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
//jump to jump dest 3 if there's more call data than just the function selector

//if there isn't anymore data, then revert. Function has to take in information
PUSH0
DUP1
REVERT

//jupdateHorseNumber jumpdest3
JUMPDEST    //  [0x0, 0x04, calldatasize, 0x43, 0x3f, func ]
POP     //  [0x04, calldatasize, 0x43, 0x3f, func ]
CALLDATALOAD    // [calldata (without function selector), calldatasize, 3F, 43, function_selector]
SWAP2   // [3F, calldatasize, calldata, 43, function_selector]
SWAP1   // [calldatasize, 3F, calldata, 43, function_selector]
POP      // [3F, calldata, 43, function_selector]
JUMP    // [calldata, 43, function_selector] -- 3f-43

//end of runtime code


//3 meta data of the code
INVALID
LOG2
PUSH5 0x6970667358
INVALID
SLT
KECCAK256
INVALID
INVALID
INVALID
PUSH27 0xff771cf69e86dc40e75701cba871cab8581706c8956ba62666eeb7
INVALID
PUSH5 0x736f6c6343
STOP
ADDMOD
EQ
STOP
CALLER