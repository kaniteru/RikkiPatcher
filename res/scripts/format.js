const eFmt = {
    "": ""
};

class Format {
    static get(fmt) {
        return Format.#INSTANCE.#getImpl(fmt);
    }

    static getAvailableLangs() {
        return Format.#INSTANCE.#getAvailableLangsImpl();
    }

    static setLang(lang) {
        Format.#INSTANCE.#setLangImpl(lang);
    }

    #getImpl(fmt) {
        const currentLangJson = this.#langJson.get(this.#currentLang);
        return currentLangJson ? currentLangJson[fmt] || null : null;
    }

    #getAvailableLangsImpl() {
        return Array.from(this.#langJson.keys());
    }

    #setLangImpl(lang) {
        this.#currentLang = lang;
    }

    constructor(lang) {
        this.#langJson = new Map();
        this.#currentLang = lang;

        const jsonArr = window.REQUEST_TRANS();

        if (jsonArr instanceof Promise) {
            jsonArr.then(data => {
                for (const [locale, json] of data) {
                    this.#langJson.set(locale, json);
                }
            });
        } else {
            for (const item of jsonArr) {
                if (Array.isArray(item) && item.length === 2) {
                    const [locale, json] = item;
                    this.#langJson.set(locale, json);
                }
            }
        }
    }

    #langJson;
    #currentLang;
    static #INSTANCE;

    static {
        Format.#INSTANCE = new Format("en_US");
    }
}