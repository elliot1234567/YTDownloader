from pytube import YouTube

def download(l, output, audioOnly):
    link = l
    yt = YouTube(link)
    if audioOnly:
        ys = yt.streams.get_audio_only()
        ys.download(output_path=output)
    else:
        ys = yt.streams.get_highest_resolution()
        ys.download(output_path=output)

def main(link, output, audioonly):
    download(link, output, audioonly)

if __name__ == "__main__":
    main()