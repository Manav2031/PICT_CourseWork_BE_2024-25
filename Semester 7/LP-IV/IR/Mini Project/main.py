# Import necessary libraries
import pandas as pd
from textblob import TextBlob

# Function to analyze sentiment using TextBlob
def analyze_sentiment(tweet_text):
    analysis = TextBlob(tweet_text)
    if analysis.sentiment.polarity > 0:
        return "Positive"
    elif analysis.sentiment.polarity == 0:
        return "Neutral"
    else:
        return "Negative"

# Function to analyze sentiment for a dataset of tweets
def analyze_tweet_dataset(file_path):
    # Load the dataset from an Excel file
    tweets_df = pd.read_excel(file_path)
    
    # Ensure the dataset contains the 'tweet' column (tweets to analyze)
    if 'tweet' not in tweets_df.columns:
        print("Dataset must have a column named 'tweet'")
        return
    
    # Add a new column 'Sentiment' to store the sentiment of each tweet
    tweets_df['Sentiment'] = tweets_df['tweet'].apply(analyze_sentiment)
    
    # Display the results
    print("\nSentiment Analysis Results:")
    print(tweets_df[['tweet', 'Sentiment']].head())
    
    return tweets_df

# Example usage of the function (change the file path to your Excel dataset)
file_path = 'dataset.xlsx'  # replace with the actual path to your Excel dataset
tweet_analysis_df = analyze_tweet_dataset(file_path)

# Optionally, you can save the result to a new CSV file
tweet_analysis_df.to_csv('tweet_analysis_output.csv', index=False)
print("\nSentiment analysis results saved to 'tweet_analysis_output.csv'")
