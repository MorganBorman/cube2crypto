//Some test data
////////////////////////////////////////////////////////////////////////////////////////

stringhashes = [
	{string: '', hash: '2339ca36c0310f42f529bb1b67e66161a7e48594d2ed373f'},
	{string: 'a', hash: '77ebbffee2e78fbae28c9fb35f787acf16e342f7f5428790'},
	{string: 'abc', hash: 'a0a2f0872ff799f2f853ea9aa76ce9b0ff6a1b0eb5af7417'},
	{string: 'message digest', hash: 'a033b07c17cf5c6f6f2bdde50922eb9509d00bec803303f7'},
	{string: 'abcdefghijklmnopqrstuvwxyz', hash: '845ffe56cce48f566d2d5b4dae629b8e8e52bde17283aeb4'},
	{string: 'abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq', hash: 'dd61d98336b2c88a5407ab5c9d9cd52829b66c20f65a9f2e'},
];

passwordhashes = [
	{cn: 0, sessionid: 0, pwd: '', hash: '8818313ef4b23397d349affb4436256e3d7d5c645c8b8278'},
	{cn: 1, sessionid: 13333, pwd: 'a', hash: '210246fac5d808b283683e38da7236672aaf41aa6d27bf3b'},
	{cn: 5, sessionid: 112211, pwd: 'abc', hash: 'da46fcd0c145d5fefe74759660272d07302d5836b6365c45'},
	{cn: 21, sessionid: 323344, pwd: 'message digest', hash: 'd753158e72f042bbea50f19675ec1a785213e3999d23ee30'},
	{cn: 117, sessionid: 13243, pwd: 'abcdefghijklmnopqrstuvwxyz', hash: '8225119b22966d3418fcc94762c629fbbf2942c68db0d247'},
	{cn: 0, sessionid: 12345, pwd: 'abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq', hash: '1fae21a15070bd4415efa2259bb02ac3ad3bcf50798cbe0a'},
];

authkeys = [
	{pwd: '', private: 'f373de2d49584e7a16166e76b1bb925f24f0130c63ac9332', public: '+2c1fb1dd4f2a7b9d81320497c64983e92cda412ed50f33aa'},
	{pwd: 'a', private: '0978245f7f243e61fca787f53bf9c82eabf87e2eeffbbe77', public: '-afe5929327bd76371626cce7585006067603daf76f09c27e'},
	{pwd: 'abc', private: '935f7b951c132951527ab541ffc5b8bff258c1e88414ab2a', public: '-d954ee56eddf2b71e206e67d48aaf4afe1cc70f8ca9d1058'},
	{pwd: 'message digest', private: 'f6295aa51aca7f511c441e754830cf0d951a2078cbf881d9', public: '-454c98466c45fce242724e6e989bdd9f841304a1fcba4787'},
	{pwd: 'abcdefghijklmnopqrstuvwxyz', private: 'e9ee7bf32f60110b2a0355ccbf120404307de5ee72a41417', public: '+15fda493cb1095ca40f652b0d208769bd42b9e234e48d1a8'},
	{pwd: 'abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq', private: '8ef7537b1e631ca7c30a4fe8f70d61b7f2589c9ba1f97b0f', public: '+643d99cb21178557f4e965eb6dc1ec1e4f57b3b05375fafb'},
];

//Test String Hashing
////////////////////////////////////////////////////////////////////////////////////////

for (var ix = 0; ix < stringhashes.length; ix++) 
{
	var test_outcome = Object();
	
	test_outcome.Name = "String Hashing #" + ix;
	
	var hashrow = stringhashes[ix];
	
	var string = hashrow.string;
	
	var hash = Module.hashstring(string, 48);
	
	test_outcome.Parameters = 	{
									'string': string,
									'correct hash': hashrow.hash,
									'given hash': hash,
								};
	
	if (hashrow.hash == hash)
	{
		test_outcome.Status = 'pass';
	}
	else
	{
		test_outcome.Status = 'fail';
	}
	
	print_test(test_outcome);
}


//Test Password Hashing
////////////////////////////////////////////////////////////////////////////////////////

for (var ix = 0; ix < passwordhashes.length; ix++) 
{
	var test_outcome = Object();
	
	test_outcome.Name = "Password Hashing #" + ix;
	
	var hashrow = passwordhashes[ix];
	
	var cn = hashrow.cn;
	var sessionid = hashrow.sessionid;
	var pwd = hashrow.pwd;
	
	var hash = Module.hashpassword(cn, sessionid, pwd);
	
	test_outcome.Parameters = 	{
									'cn': cn,
									'sessionid': sessionid,
									'pwd': pwd,
									'correct hash': hashrow.hash,
									'given hash': hash,
								};
	
	if (hashrow.hash == hash)
	{
		test_outcome.Status = 'pass';
	}
	else
	{
		test_outcome.Status = 'fail';
	}
	
	print_test(test_outcome);
}


//Test Auth key generation
////////////////////////////////////////////////////////////////////////////////////////

for (var ix = 0; ix < authkeys.length; ix++) 
{
	var test_outcome = Object();
	
	test_outcome.Name = "KeyGen #" + ix;
	
	var keypair = authkeys[ix];
	var seed = keypair.pwd;
	var generated_keypair = Module.genkeypair(seed);
	
	test_outcome.Parameters = 	{
									'reference private key': keypair.private,
									'reference public key': keypair.public,
									'seed string': seed,
									'generated private key': generated_keypair[0],
									'generated public key': generated_keypair[1],
								};
	
	if (keypair.private == generated_keypair[0] && keypair.public == generated_keypair[1])
	{
		test_outcome.Status = 'pass';
	}
	else
	{
		test_outcome.Status = 'fail';
	}
	
	print_test(test_outcome);
}

//Test Public key recovery
////////////////////////////////////////////////////////////////////////////////////////

for (var ix = 0; ix < authkeys.length; ix++) 
{
	var test_outcome = Object();
	
	test_outcome.Name = "Get public key #" + ix;
	
	var keypair = authkeys[ix];
	var pubkey = Module.getpubkey(keypair.private);
	
	test_outcome.Parameters = 	{
									'reference private key': keypair.private,
									'reference public key': keypair.public,
									'generated public key': pubkey,
								};
	
	if (keypair.public == pubkey)
	{
		test_outcome.Status = 'pass';
	}
	else
	{
		test_outcome.Status = 'fail';
	}
	
	print_test(test_outcome);
}

//Test Challenge and answer generation
////////////////////////////////////////////////////////////////////////////////////////
	
for (var ix = 0; ix < authkeys.length; ix++) 
{
	var test_outcome = Object();
	
	test_outcome.Name = "Challenges #" + ix;
	
	var keypair = authkeys[ix];
	var seed = keypair.pwd;
	var challengepair = Module.genchallenge(keypair.public, seed);
	var answer = Module.answerchallenge(keypair.private, challengepair[0]);
	
	
	test_outcome.Parameters = 	{
										'private key': keypair.private,
										'public key': keypair.public,
										'seed string': seed,
										'challenge': challengepair[0],
										'correct answer': challengepair[1],
										'given answer': answer,
									};
	
	if (challengepair[1] == answer)
	{
		test_outcome.Status = 'pass';
	}
	else
	{
		test_outcome.Status = 'fail';
	}
	
	print_test(test_outcome);
}





















