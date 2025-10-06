using AEssentials;
using System.Collections;
using System.Collections.Generic;
using UnityEngine;

public class SoundManager : Singleton<SoundManager>
{
    [Header("Settings")]
    [Range(0f, 1f)]
    public float mainVolume;
    [Range(0f, 1f)]
    public float soundEffectVolume;
    [Range(0f, 1f)]
    public float musicVolume;

    [Header("References")]
    public AudioSource soundFXObject;
    [SerializeField] int poolSize;

    Queue<AudioSource> audioPool = new Queue<AudioSource>();

    void Start()
    {
        InitializePool();        
    }

    void InitializePool()
    {
        for (int i = 0; i < poolSize; i++)
        {
            AudioSource source = Instantiate(soundFXObject, transform);
            source.gameObject.SetActive(false);
            audioPool.Enqueue(source);
        }
    }

    public AudioSource GetFromAudioPool()
    {
        if (audioPool.Count > 0)
        {
            AudioSource source = audioPool.Dequeue();
            source.gameObject.SetActive(true);
            return source;
        }
        else
        {
            AudioSource source = Instantiate(soundFXObject, transform);
            return source;
        }
    }

    public void ResetAudioSource(AudioSource source)
    {
        //Skip this if the audiosource got destroyed
        if (source == null) return;

        // Resets the audiosource
        source.Stop();
        source.clip = null;
        source.pitch = 1;
        source.spatialBlend = 1;
        source.loop = false;
        source.transform.SetParent(transform, true);
        source.gameObject.SetActive(false);

        audioPool.Enqueue(source);
    }

    public SoundObject PlayMusic(AudioClip audioClip, Vector3 spawnPos, Transform followObject = null, float volume = 1, bool looping = false, float pitch = 1f, float fadeOutLength = 0, bool mono = false)
    {
        return new SoundObject(audioClip, spawnPos, volume, followObject, looping, pitch, fadeOutLength, mono, true);
    }

    public SoundObject PlaySoundFX(AudioClip audioClip, Vector3 spawnPos, Transform followObject = null, float volume = 1)
    {
        return new SoundObject(audioClip, spawnPos, volume, followObject, false, 1, 0, false, false);
    }

    public SoundObject PlaySoundFX(AudioClip audioClip, Vector3 spawnPos, Transform followObject = null, float volume = 1, bool looping = false, float pitch = 1f, float fadeOutLength = 0, bool mono = false)
    {
        return new SoundObject(audioClip, spawnPos, volume, followObject, looping, pitch, fadeOutLength, mono, false);
    }

    public IEnumerator WaitForReturnToAudioPool(AudioSource audioSource)
    {
        yield return new WaitForSeconds(audioSource.clip.length);
        ResetAudioSource(audioSource);
    }

    public IEnumerator FadeOutSoundClip(AudioSource audioSource, float fadeOutLength, bool fadeOutNow)
    {
        if (!fadeOutNow)
        {
            float waitTime = audioSource.clip.length - fadeOutLength;
            yield return new WaitForSeconds(waitTime);
        }

        float timeElapsed = 0;
        float startVolume = audioSource.volume;

        while (timeElapsed < fadeOutLength)
        {
            if (audioSource == null) yield break;

            audioSource.volume = Mathf.Lerp(startVolume, 0f, timeElapsed / fadeOutLength);
            timeElapsed += Time.deltaTime;
            yield return null;
        }

        ResetAudioSource(audioSource);
    }
}

public class SoundObject
{
    Coroutine activeCoroutine;
    AudioClip audioClip;
    AudioSource audioSource;

    Vector3 spawnPos;
    float volume;
    Transform followObject;
    bool loop;
    float pitch;
    float fadeOutLength;
    bool mono;
    bool isMusic;

    public SoundObject(AudioClip audioClip, Vector3 spawnPos, float volume, Transform followObject, bool loop, float pitch, float fadeOutLength, bool mono, bool isMusic)
    {
        this.audioClip = audioClip;
        this.spawnPos = spawnPos;
        this.volume = volume;
        this.followObject = followObject;
        this.loop = loop;
        this.pitch = pitch;
        this.fadeOutLength = fadeOutLength;
        this.mono = mono;
        this.isMusic = isMusic;

        PlaySound();
    }

    void PlaySound()
    {
        if (audioClip == null)
        {
            Debug.LogWarning("SoundFXManager: audioClip is null!");
            return;
        }

        audioSource = SoundManager.Instance.GetFromAudioPool();
        audioSource.transform.position = spawnPos;
        audioSource.clip = audioClip;
        audioSource.pitch = pitch;
        if (isMusic)
        {
            audioSource.volume = volume * SoundManager.Instance.mainVolume * SoundManager.Instance.musicVolume;
        }
        else
        {
            audioSource.volume = volume * SoundManager.Instance.mainVolume * SoundManager.Instance.soundEffectVolume;
        }

        if (followObject != null)
        {
            audioSource.transform.SetParent(followObject.transform, true);
        }
        if (mono)
        {
            audioSource.spatialBlend = 0;
        }

        audioSource.Play();

        if (!loop)
        {
            if (fadeOutLength > 0)
            {
                activeCoroutine = SoundManager.Instance.StartCoroutine(SoundManager.Instance.FadeOutSoundClip(audioSource, fadeOutLength, false));
            }
            else
            {
                activeCoroutine = SoundManager.Instance.StartCoroutine(SoundManager.Instance.WaitForReturnToAudioPool(audioSource));
            }            
        }
        else
        {
            audioSource.loop = loop;
        }
    }

    public void Pause()
    {
        if (audioSource == null) return;

        audioSource.Pause();
    }

    public void Resume()
    {
        if (audioSource == null) return;

        audioSource.UnPause();
    }

    /// <summary>
    /// StopPlaying will destroy and reset the SoundFXObject.
    /// </summary>
    public void StopPlaying()
    {
        if (audioSource == null) return;

        if (activeCoroutine != null)
        {
            SoundManager.Instance.StopCoroutine(activeCoroutine);
            SoundManager.Instance.ResetAudioSource(audioSource);
            activeCoroutine = null;
        }
        else
        {
            SoundManager.Instance.ResetAudioSource(audioSource);
        }
    }

    /// <summary>
    /// The fadeOutLength parameter specifies the length to fadeout starting from the current time of the audioclip<br/>
    /// If parameter fadeOutLength is unused or set to zero, the fadeout will be the the remaining length of the audioclip
    /// </summary>
    public void StopPlayingWithFadeOut(float fadeOutLength = 0)
    {
        if (audioSource == null) return;

        if (activeCoroutine != null)
        {
            SoundManager.Instance.StopCoroutine(activeCoroutine);
            activeCoroutine = null;
        }

        float timeRemaining = audioSource.clip.length - audioSource.time;

        if (fadeOutLength != 0 && timeRemaining > fadeOutLength)
        {
            activeCoroutine = SoundManager.Instance.StartCoroutine(SoundManager.Instance.FadeOutSoundClip(audioSource, fadeOutLength, true));
        }
        else
        {
            activeCoroutine = SoundManager.Instance.StartCoroutine(SoundManager.Instance.FadeOutSoundClip(audioSource, timeRemaining, true));
        }
    }
}