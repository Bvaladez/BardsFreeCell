
Rank = [1,2,3,4,5,6,7,8,9,10,"j", "k","q"]
Suit = ["c","d","h","s"]

def main():
	fin = open("Scooby.deck", 'w')
	for rank in Rank:
		for suit in Suit:
			fin.write("ScoobyDeck/scooby" + str(rank) + str(suit) + ".jpg" +"\n")
	return

if __name__ == '__main__':
	main()