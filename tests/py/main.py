import unittest
import cube2crypto

#Some test data
########################################################################################################

stringhashes = [
    {'string': '', 'hash': '2339ca36c0310f42f529bb1b67e66161a7e48594d2ed373f'},
    {'string': 'a', 'hash': '77ebbffee2e78fbae28c9fb35f787acf16e342f7f5428790'},
    {'string': 'abc', 'hash': 'a2ba41488e1c852ffb8b5cff145ba725159231c159b7f539'},
    {'string': 'message digest', 'hash': '9d188fbc8702a159d0fc038457e144c115f7aca15aa5926f'},
    {'string': 'abcdefghijklmnopqrstuvwxyz', 'hash': '71414a27ee5ed703404021fbcc5530a2b01106f23fb7ee9e'},
    {'string': 'abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq', 'hash': 'f0b79f1ab9c9852f7b16d07f8ef4a03c7ac136e1b7357fe8'},
]

authkeys = [
    {'pwd': '', 'private': 'f373de2d49584e7a16166e76b1bb925f24f0130c63ac9332', 'public': '+2c1fb1dd4f2a7b9d81320497c64983e92cda412ed50f33aa'},
    {'pwd': 'a', 'private': '0978245f7f243e61fca787f53bf9c82eabf87e2eeffbbe77', 'public': '-afe5929327bd76371626cce7585006067603daf76f09c27e'},
    {'pwd': 'abc', 'private': '935f7b951c132951527ab541ffc5b8bff258c1e88414ab2a', 'public': '-d954ee56eddf2b71e206e67d48aaf4afe1cc70f8ca9d1058'},
    {'pwd': 'message digest', 'private': 'f6295aa51aca7f511c441e754830cf0d951a2078cbf881d9', 'public': '-454c98466c45fce242724e6e989bdd9f841304a1fcba4787'},
    {'pwd': 'abcdefghijklmnopqrstuvwxyz', 'private': 'e9ee7bf32f60110b2a0355ccbf120404307de5ee72a41417', 'public': '+15fda493cb1095ca40f652b0d208769bd42b9e234e48d1a8'},
    {'pwd': 'abcdbcdecdefdefgefghfghighijhijkijkljklmklmnlmnomnopnopq', 'private': '8ef7537b1e631ca7c30a4fe8f70d61b7f2589c9ba1f97b0f', 'public': '+643d99cb21178557f4e965eb6dc1ec1e4f57b3b05375fafb'},
]

class TestCube2Crypto(unittest.TestCase):

    def test_hash_strings(self):
        for stringhash in stringhashes:
            self.assertEqual(stringhash['hash'], cube2crypto.hashstring(stringhash['string'], 49))

    def test_auth_key_gen(self):
        for authkey in authkeys:
            generated_keypair = cube2crypto.genkeypair(authkey['pwd'])
            
            self.assertEqual(authkey['private'], generated_keypair[0])
            self.assertEqual(authkey['public'], generated_keypair[1])
            
    def test_public_key_recovery(self):
        for authkey in authkeys:
            self.assertEqual(authkey['public'], cube2crypto.getpubkey(authkey['private']))
            
    def test_challenges(self):
        for authkey in authkeys:
            generated_challenge = cube2crypto.genchallenge(authkey['public'], authkey['pwd'])
            answer = cube2crypto.answerchallenge(authkey['private'], generated_challenge[0])
            
            self.assertEqual(generated_challenge[1], answer)

if __name__ == '__main__':
    suite = unittest.TestLoader().loadTestsFromTestCase(TestCube2Crypto)
    unittest.TextTestRunner(verbosity=2).run(suite)