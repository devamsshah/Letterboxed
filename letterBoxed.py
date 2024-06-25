import string

class LetterBoxedGame:
    def __init__(self, letters):
        self.letters = letters
        self.sides = {
            "top": letters[0:2],
            "right": letters[2:4],
            "bottom": letters[4:6],
            "left": letters[6:8]
        }
    
    def is_valid_word(self, word):
        used_sides = set()
        
        for letter in word.upper():
            for side, side_letters in self.sides.items():
                if letter in side_letters:
                    used_sides.add(side)
                    break
            else:
                return False  # Letter not found on any side

        # Check if at least one letter from each side is used
        if len(used_sides) == 4:
            return True
        
        return False
    
    def play(self):
        print("Welcome to the Letter Boxed Game!")
        print(f"Letters: {', '.join(self.letters)}")
        print("Form words using letters from different sides of the box.")
        print("Each word must use at least one letter from each of the four sides.")
        print("Words must be at least 4 letters long.")
        
        while True:
            word = input("Enter a word (or 'exit' to quit): ")
            
            if word.lower() == 'exit':
                break
            
            if len(word) < 4:
                print("Word is too short. Words must be at least 4 letters long.")
                continue
            
            if self.is_valid_word(word):
                print(f"{word} is a valid word!")
            else:
                print(f"{word} is not a valid word. Try again.")
        
        print("Thanks for playing!")

# Set up the letters on the edges of the box
letters = ["A", "B", "D", "E", "F", "G", "N", "I"]
game = LetterBoxedGame(letters)
game.play()
