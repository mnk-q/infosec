

from random import shuffle

emojis = '''😀😃😄😁😆😅😂🤣😊😇🙂🙃😉😌😍🥰😘😗😙😚😋😛😝😜🤪🤨🧐🤓😎🥸🤩🥳😏😒😞😔😟😕🙁☹️😓😥😰😨😱😶🥶🥵😳🤯🤬😡😠😑😭😤😢🥺😩😛😖😣🤗🤔🤭🤫🤥😶😐😑😬🙄😯😦😧😮🥱😴😪😮‍💨😵👽☠️💀👻💩🤡👺👹👿😈🤠🤑🤕🧐🤒😷🤧🤮🤢😛🥴🤐😵🤲🙌👏🤝👍👎👊✊🤛🤜🎵🔔🍎⚽🏀🏹🎧🎼🎹🥁🪘🏆📀📷📸❤️🇮🇳🇱🇷🇺🇸🇧🇷💥🔥🌪️🌈💧💦🌊⭐💫✨⚡✈️🛩️💺🚀🛸🚁🛶⛵🚤🛥️🛳️⛴️🚢⚓🪝🌠🎇🕋🛕🛖🕌⛪⛩️🛤️🛣️📱🖥️🖨️🖱️🖲️🕹️🗜️🧸📉📯🏮📃📜🎉🗂️🎊🪅🪄🎎❗❕❓❔‼️⁉️🔅🔆〽️⚠️✴️🏴‍☠️🏳️💍🪖👑🥽🎒👜👙👗👘🩱👚🙇‍♀️🙇‍♂️💁‍♀️💁‍♂️🙅‍♀️🙅‍♂️🙆‍♀️🙆‍♂️🙋‍♀️🙋‍♂️🧏‍♂️🤦‍♀️🤦‍♂️🤷‍♀️🤷‍♂️🙎‍♀️🙎‍♂️🙍‍♀️🙍‍♂️'''
em_dict = {i: emojis[i] for i in range(len(emojis))}
em_rev_dict = {emojis[i]:i for i in range(len(emojis))}
def long_as_msg(key, l):
    while len(key) < l:
        key += key
    return key[:l]

def monoalphabetic_key_generation():
    """Generates a random key of length 26"""
    psr = [chr(i) for i in range(97,97+26)]
    shuffle(psr)
    return ''.join(psr)

def emoji_convert(msg):
    em = []
    for i in msg:
        em.append(em_dict[ord(i)])
        
    return ''.join(em)

def emoji_bring_back(msg):
    m = []
    for e in msg:
        m.append(chr(em_rev_dict[e]))
    return ''.join(m)