import logging

def word_count(myfile):
    logging.basicConfig(
        level=logging.DEBUG, 
        filename='/Users/sam/Workspace/Academic Assignments/CSDF/lab 4/word_count_logger.log',
        format='%(asctime)s %(levelname)s:%(message)s',
        filemode='w'
    )

    try:
        with open(myfile, 'r') as f:
            file_data = f.read()
            words = file_data.split(" ")
            num_words = len(words)
            logging.debug("this file has %d words", num_words)
            return num_words
    except OSError as e:
        logging.error("error reading the file")

if __name__ == "__main__":
    word_count("/Users/sam/Workspace/Academic Assignments/CSDF/lab 4/words.txt")